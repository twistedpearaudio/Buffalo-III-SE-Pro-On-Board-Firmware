// Copyright (c) 2017 Russ White
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdlib.h>
#include <avr/wdt.h>
#include "USI_I2C_Master.h"
#include "Buffalo.h"
#include "ES9028_38.h"

// switch states coming from the port expander
SW1 sw1;
SW2 sw2;

// desired DAC state
uint8_t lastVol;

// array to hold ADC samples for volume
uint8_t volumeResults[AVG_LEN];

// use for quick sort
int cmp_chars(const void *c1, const void *c2) {
	uint8_t ch1 = *(uint8_t *) c1;
	uint8_t ch2 = *(uint8_t *) c2;
	return ch1 - ch2;
}

// sends a byte to the target address awaiting start condition
// the start must be successful to move on
void i2cSendByte(uint8_t address, uint8_t reg, uint8_t val) {
	if (i2c_start(address) == 0) {
		i2c_write(reg);
		i2c_write(val);
		i2c_stop();
	} else {
		i2cSendByte(address, reg, val);
	}
}

// receives a byte to the target address awaiting start condition
// the start must be successful to move on
// this prevents initializing while the DAC is not ready
uint8_t i2cReceiveByte(uint8_t address, uint8_t reg) {
	uint8_t res = 0;
	if (i2c_start(address) == 0) {
		i2c_write(reg);
		i2c_stop();
		i2c_start(address + 1);
		res = i2c_read(1); // send nack
		i2c_stop();
	} else {
		_delay_ms(1);
		res = i2cReceiveByte(address, reg);
	}
	return res;
}

// apply the volume to channel 1 only!
void setVolume(uint8_t vol) {
	uint8_t v = 127 - vol;
	if (v >= 126)
		v = 255; // close to mute
	if (v != lastVol)
		i2cSendByte(DAC_ADDRESS, 16, v);
	lastVol = v;
}

// gets the reading from the ADC and applies some over-sampling to get smoother reading.
// this is faster than averaging
uint8_t getVolume() {
	uint8_t i;
	//Remove jitter from ADC reading
	for (i = 0; i < AVG_LEN; i++) {
		ADCSRA |= _BV(ADSC); // set
		while (ADCSRA & _BV(ADSC))
		volumeResults[i] = (ADCH >> 1);
	}
	qsort(volumeResults, AVG_LEN, sizeof(uint8_t), &cmp_chars);
	return volumeResults[AVG_LEN / 2];
}

// This does all the heavy lifting of configuring the state based on the switches
void configureDAC() {
	// configurable stuff:
	R1_INPUT_SELECTION r1;
	r1.byte = R1_DEFAULT;
	if (sw1.input_mode == INPUT_MODE_SERIAL) {
		r1.auto_select = R1_AUTO_SELECT_DSD_SERIAL;
		r1.input_select = R1_INPUT_SELECT_SERIAL;
	} else {
		r1.auto_select = R1_AUTO_SELECT_DISABLE;
		r1.input_select = R1_INPUT_SELECT_SPDIF;
	}
	i2cSendByte(DAC_ADDRESS, 1, r1.byte);

	R2_SERIAL_DATA_AUTOMUTE_CONFIG r2;
	r2.byte = R2_DEFAULT;
	if (sw2.automute_enable) r2.automute_config = R2_AUTOMUTE_CONFIG_MUTE;
	switch(sw1.serial_format) {
		case 0 :
			r2.serial_mode = R2_SERIAL_MODE_I2S;
			break;
		case 1 :
			r2.serial_mode = R2_SERIAL_MODE_LJ;
			break;
		case 3 :
			r2.serial_mode = R2_SERIAL_MODE_RJ;
			break;
		default :
			r2.serial_mode = R2_SERIAL_MODE_I2S;
	}
	switch(sw1.serial_length) {
		case 0:
			r2.serial_length = R2_SERIAL_LENGTH_32;
			r2.serial_bits = R2_SERIAL_BITS_32;
			break;
		case 1:
			r2.serial_length = R2_SERIAL_LENGTH_24;
			r2.serial_bits = R2_SERIAL_BITS_24;
			break;
		case 2:
			r2.serial_length = R2_SERIAL_LENGTH_16;
			r2.serial_bits = R2_SERIAL_BITS_16;
			break;
		default:
			r2.serial_length = R2_SERIAL_LENGTH_32;
			r2.serial_bits = R2_SERIAL_BITS_32;
	}
	i2cSendByte(DAC_ADDRESS, 2, r2.byte);

	R4_AUTOMUTE_TIME r4;
	r4.byte = R4_DEFAULT;
	if (sw2.automute_enable) r4.automute_time = 4;
	i2cSendByte(DAC_ADDRESS, 4, r4.byte);

	R7_FILTER_BW_SYSTEM_MUTE r7;
	r7.byte = R7_DEFAULT;
	r7.filter_shape = sw1.filter;
	r7.iir_bw = sw2.iir_bw;
	i2cSendByte(DAC_ADDRESS, 7, r7.byte);

	R8_GPIO_1_2_CONFIG r8;
	r8.byte = R8_DEFAULT;
	r8.gpio1_cfg = GPIO_OUT_AUTOMUTE_STATUS;
	r8.gpio2_cfg = GPIO_IN_STANDARD_INPUT;
	i2cSendByte(DAC_ADDRESS, 8, r8.byte);

	R9_GPIO_3_4_CONFIG r9;
	r9.byte = R9_DEFAULT;
	r9.gpio3_cfg = GPIO_IN_STANDARD_INPUT;
	r9.gpio4_cfg = GPIO_OUT_LOCK_STATUS;
	i2cSendByte(DAC_ADDRESS, 9, r9.byte);

	R11_SPDIF_MUX_GPIO_INVERT r11;
	r11.byte = R11_DEFAULT;
	r11.spdif_sel = 3;
	i2cSendByte(DAC_ADDRESS, 11, r11.byte);

	R12_JE_DPLL_BW r12;
	uint8_t dpll = sw2.dpll;
	// we don't ever want the DPLL to be off
	if (dpll == 0) dpll = 5;
	r12.byte = R12_DEFAULT;
	r12.dpll_bw_serial = dpll;
	r12.dpll_bw_dsd = dpll;
	i2cSendByte(DAC_ADDRESS, 12, r12.byte);

	R13_JE_THD_COMP_CONFIG r13;
	r13.byte = R13_DEFAULT;
	i2cSendByte(DAC_ADDRESS, 13, r13.byte);

	R15_GPIO_INPUT_SEL_VOLUME_CONFIG r15;
	r15.byte = R15_DEFAULT;
	r15.stereo_mode = R15_STEREO_MODE_ENABLED;
	r15.use_only_ch1_vol = R15_USE_ONLY_CH1_VOLUME_ENABLED;
	r15.latch_vol = R15_LATCH_VOLUME_ENABLED;
	i2cSendByte(DAC_ADDRESS, 15, r15.byte);

	R37_PROGRAMMABLE_FIR_CONFIG r37;
	r37.byte = R37_DEFAULT;
	if (sw2.osf_bypass) {
		r37.bypass_osf = R37_OSF_DISABLED;
	} else {
		r37.bypass_osf = R37_OSF_ENABLED;
	}
	i2cSendByte(DAC_ADDRESS, 37, r37.byte);
}

// read the port expander switch states
void readSwitchStates() {
	uint8_t s1 = i2cReceiveByte(PE_ADDRESS, PE_GPIOA);
	uint8_t s2 = i2cReceiveByte(PE_ADDRESS, PE_GPIOB);
	if (s1 != sw1.byte || s2 != sw2.byte) {
		sw1.byte = s1;
		sw2.byte = s2;
		configureDAC();
	}
}

void initialize() {
	// ADC setup
	// set DDRB4 to input
	cbi(DDRB, PIN4);
	// disable weak pull-up on PORTB4
	cbi(PORTB, PIN4);
	// setup ADC
	ADCSRA = 0;
	ADMUX = 0;
	sbi(ADMUX, ADLAR);
	cbi(ADMUX, MUX0);
	sbi(ADMUX, MUX1);
	cbi(ADMUX, MUX2);
	cbi(ADMUX, MUX3);
	cbi(ADMUX, REFS0);
	cbi(ADMUX, REFS1);

	cbi(ADCSRA, ADEN);
	sbi(ADCSRA, ADPS2);
	sbi(ADCSRA, ADPS1);
	sbi(ADCSRA, ADPS0);
	sbi(ADCSRA, ADEN);

	// setup I2C
	i2c_init();
	_delay_ms(1);
	// configure the port expander
	i2cSendByte(PE_ADDRESS, PE_IOCONN, 0b00100000);	// we will only be sending one byte at a time
	_delay_ms(1);
	i2cSendByte(PE_ADDRESS, PE_GPPUA, 0b11111111); // enable all weak pull-ups
	i2cSendByte(PE_ADDRESS, PE_GPPUB, 0b11111111); // enable all weak pull-ups
	_delay_ms(10);
	// GET the initial state for the DAC registers
	readSwitchStates();
}

// Main
int main(int argc, char **argv) {
	// keep DAC in reset
	sbi(DDRB, PIN1);
	cbi(PORTB, PIN1);
	_delay_ms(1500);
	// bring DAC out of reset
	sbi(PORTB, PIN1);
	initialize();
	// Continually check the state/ADC and apply changes to the DAC(s)
	configureDAC();
	uint8_t counter = 0;
	while (1) {
		setVolume(getVolume());
		_delay_ms(30); // sleep a bit
		// we only want to check the switch state about 3 times per second
		if (counter == 10) {
			counter = 0;
			readSwitchStates();
		}
		counter++;
	}
	return 0;
}

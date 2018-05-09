// Copyright (c) 2017 Russ White

#ifndef BUFFALO_H_
#define BUFFALO_H_
#define DAC_ADDRESS 			0x90

#define PE_ADDRESS  			0x40

#define sbi(sfr, bit) 		(_SFR_BYTE(sfr) |= _BV(bit))
#define cbi(sfr, bit) 		(_SFR_BYTE(sfr) &= ~_BV(bit))

#define AVG_LEN 8 // The number of times to sample ADC

#define PE_IOCONN			0x0A// at least initially
#define PE_IPOLA  			0x02
#define PE_IPOLB  			0x03
#define PE_GPPUA  			0x0C
#define PE_GPPUB  			0x0D
#define PE_GPIOA				0x12
#define PE_GPIOB				0x13

#endif /* BUFFALO_H_ */



// input modes
#define INPUT_MODE_SPDIF 	 	0
#define INPUT_MODE_SERIAL 	 	1

// serial input formats
#define SERIAL_FORMAT_I2S 	 	0
#define SERIAL_FORMAT_LJ 	 	1
#define SERIAL_FORMAT_RJ 	 	2

// serial data lengths
#define SERIAL_32_BIT			0
#define SERIAL_24_BIT			1
#define SERIAL_16_BIT			3


#define INPUT_MODE_SERIAL 	 	1
#define OUTPUT_MODE_STEREO 	 	0
#define OUTPUT_MODE_MONO 		1
// output normalization (auto calibration via ADC)
// when enabled output will be the same across modules at the cost of reduced dynamic range.
// for highest fidelity in stereo mode leave it off
#define OUTPUT_NORMALIZER_OFF 	0
#define OUTPUT_NORMALIZER_ON 	1

typedef union {
	// the factory state for the switches is "on"
	// the switches close to GND so "on" is 0 (low) and "off" is 1 (high)
	struct {
		uint8_t input_mode :1;
		uint8_t serial_format :2;
		uint8_t serial_length :2;
		// this maps directly to the DAC filter registers ON = 0 Off = 1
		uint8_t filter :3;
	};
	uint8_t byte;
} SW1;


typedef union {
	struct {
		uint8_t automute_enable :1;
		uint8_t gear :1;
		uint8_t iir_bw :2;
		uint8_t dpll :4;
	};
	uint8_t byte;
} SW2;


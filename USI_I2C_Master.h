// Copyright (c) 2016 Russ White

#ifndef USI_I2C_Master_h
#define USI_I2C_Master_h

//#define I2C_FAST_MODE 1
#ifdef I2C_FAST_MODE
#define T2_I2C	1.3
#define T4_I2C	0.6
#else
#define T2_I2C	4.7
#define T4_I2C	4.0
#endif

#define SIGNAL_VERIFY

/****************************************************************************
 Bit and byte definitions
 ****************************************************************************/
#define I2C_READ_BIT  0       // Bit position for R/W bit in "address byte".
#define I2C_ADR_BITS  1       // Bit position for LSB of the slave address bits in the init byte.
#define I2C_NACK_BIT  0       // Bit position for (N)ACK bit.

// Note these have been renumbered from the Atmel Apps Note. Most likely errors are now
//		lowest numbers so they're easily recognized as LED flashes.
#define USI_I2C_NO_DATA             0x08  // Transmission buffer is empty
#define USI_I2C_DATA_OUT_OF_BOUND   0x09  // Transmission buffer is outside SRAM space
#define USI_I2C_UE_START_CON        0x07  // Unexpected Start Condition
#define USI_I2C_UE_STOP_CON         0x06  // Unexpected Stop Condition
#define USI_I2C_UE_DATA_COL         0x05  // Unexpected Data Collision (arbitration)
#define USI_I2C_NO_ACK_ON_DATA      0x02  // The slave did not acknowledge  all data
#define USI_I2C_NO_ACK_ON_ADDRESS   0x01  // The slave did not acknowledge  the address
#define USI_I2C_MISSING_START_CON   0x03  // Generated Start Condition not detected on bus
#define USI_I2C_MISSING_STOP_CON    0x04  // Generated Stop Condition not detected on bus
#define USI_I2C_BAD_MEM_READ	    0x0A  // Error during external memory read

// Device dependent defines
#if defined(__AVR_AT90Mega169__) | defined(__AVR_ATmega169__) | \
    defined(__AVR_AT90Mega165__) | defined(__AVR_ATmega165__) | \
    defined(__AVR_ATmega325__) | defined(__AVR_ATmega3250__) | \
    defined(__AVR_ATmega645__) | defined(__AVR_ATmega6450__) | \
    defined(__AVR_ATmega329__) | defined(__AVR_ATmega3290__) | \
    defined(__AVR_ATmega649__) | defined(__AVR_ATmega6490__)
#define DDR_USI             DDRE
#define PORT_USI            PORTE
#define PIN_USI             PINE
#define PORT_USI_SDA        PORTE5
#define PORT_USI_SCL        PORTE4
#define PIN_USI_SDA         PINE5
#define PIN_USI_SCL         PINE4
#endif

#if defined(__AVR_ATtiny25__) | defined(__AVR_ATtiny45__) | defined(__AVR_ATtiny85__) | \
    defined(__AVR_AT90Tiny26__) | defined(__AVR_ATtiny26__)
#define DDR_USI             DDRB
#define PORT_USI            PORTB
#define PIN_USI             PINB
#define PORT_USI_SDA        PB0	//originally PORTB0
#define PORT_USI_SCL        PB2	//originally PORTB2
#define PIN_USI_SDA         PINB0
#define PIN_USI_SCL         PINB2
#endif

#if defined(__AVR_ATtiny24__) | defined(__AVR_ATtiny44__) | defined(__AVR_ATtiny84__)
#define DDR_USI             DDRA
#define PORT_USI            PORTA
#define PIN_USI             PINA
#define PORT_USI_SDA        PA6	//PORTA6
#define PORT_USI_SCL        PA4	//PORTA4
#define PIN_USI_SDA         PINA6
#define PIN_USI_SCL         PINA4
#endif

#if defined(__AVR_AT90Tiny2313__) | defined(__AVR_ATtiny2313__)
#define DDR_USI             DDRB
#define PORT_USI            PORTB
#define PIN_USI             PINB
#define PORT_USI_SDA        PORTB5
#define PORT_USI_SCL        PORTB7
#define PIN_USI_SDA         PINB5
#define PIN_USI_SCL         PINB7
#endif

// General defines
#define TRUE  1
#define FALSE 0

//********** Prototypes **********//

void i2c_init(void);
uint8_t i2c_get_state_info(void);
uint8_t i2c_start(uint8_t);
uint8_t i2c_rep_start(uint8_t);
uint8_t i2c_stop(void);
uint8_t i2c_write(uint8_t);
uint8_t i2c_read(uint8_t);

#endif

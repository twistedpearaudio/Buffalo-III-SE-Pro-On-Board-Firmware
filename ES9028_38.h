/*
 * ES9028_38.h
 *
 *  Created on: Aug 26, 2017
 *      Author: Russ
 */

#ifndef ES9028_38_H_
#define ES9028_38_H_

typedef uint8_t B;

// These are the hardware defaults at reset according to the ES9028 data sheet

// System Registers
#define R0_DEFAULT              0b00000000

#define R0_CLOCK_GEAR_DIV_1     0b00
#define R0_CLOCK_GEAR_DIV_2     0b01
#define R0_CLOCK_GEAR_DIV_4     0b10
#define R0_CLOCK_GEAR_DIV_8     0b11

#define R0_OSC_DRV_OFF          0b0000
#define R0_OSC_DRV_25PCT        0b1110
#define R0_OSC_DRV_50PCT        0b1100
#define R0_OSC_DRV_75PCT        0b1000
#define R0_OSC_DRV_FULL         0b0000

typedef union {
    struct {
        B soft_reset :1;
        B reserved :1;
        B clk_gear :2;
        B osc_drv :4;
    };
    B byte;
} R0_SYSTEM;

// Register 1: Input Selection
#define R1_DEFAULT                      0b00001100

#define R1_AUTO_SELECT_ALL              0b11
#define R1_AUTO_SELECT_SPDIF_SERIAL     0b10
#define R1_AUTO_SELECT_DSD_SERIAL       0b01
#define R1_AUTO_SELECT_DISABLE          0b00

#define R1_INPUT_SELECT_DSD             0b11
#define R1_INPUT_SELECT_SPDIF           0b01
#define R1_INPUT_SELECT_SERIAL          0b00

#define R1_SPDIF_VALID_MUTE             0b0
#define R1_SPDIF_VALID_IGNORE           0b1

#define R1_SPDIF_DATA_MUTE              0b0
#define R1_SPDIF_DATA_IGNORE            0b1

#define R1_SPDIF_BITS_USER              0b1
#define R1_SPDIF_BITS_STATUS            0b0

typedef union {
    struct {
        B input_select :2;
        B auto_select :2;
        B reserved :1;
        B spdif_valid_toggle :1;
        B spdif_data_toggle :1;
        B spdif_bits_toggle :1;
    };
    B byte;
} R1_INPUT_SELECTION;

// Register 2: Serial Data Configuration and Automute Enable
#define R2_DEFAULT                          0b00111100

// Automute configuration
#define R2_AUTOMUTE_CONFIG_MUTE_THEN_GND    0b11
#define R2_AUTOMUTE_CONFIG_GND              0b10
#define R2_AUTOMUTE_CONFIG_MUTE             0b01
#define R2_AUTOMUTE_CONFIG_NORMAL_OPERATION 0b00

// Note Serial length is almost always 32
// Serial bits can almost always be 32 as well for I2S.
// Actual size of the word
#define R2_SERIAL_BITS_32                   0b11
#define R2_SERIAL_BITS_24                   0b01
#define R2_SERIAL_BITS_16                   0b00

// DATA_CLK pulses per word
#define R2_SERIAL_LENGTH_32                 0b11
#define R2_SERIAL_LENGTH_24                 0b01
#define R2_SERIAL_LENGTH_16                 0b00

// Mode
#define R2_SERIAL_MODE_RJ                   0b11
#define R2_SERIAL_MODE_LJ                   0b01
#define R2_SERIAL_MODE_I2S                  0b00

typedef union {
    struct {
        B serial_mode :2;
        B serial_length :2;
        B serial_bits :2;
        B automute_config :2;
    };
    B byte;
} R2_SERIAL_DATA_AUTOMUTE_CONFIG;

// Register 3: Reserved
#define R3_DEFAULT          0b00000000 // This is a reserved register

// Register 4: Automute Time.
#define R4_DEFAULT          0b00000000

typedef union {
    B automute_time;
    B byte;
} R4_AUTOMUTE_TIME;

// Register 5: Trigger level in decibels for automute function
// The default is -104db
#define R5_DEFAULT          0b01110010

typedef union {
    struct {
        B automute_level :7;
        B reserved :1;
    };
    B byte;
} R5_AUTOMUTE_LEVEL;

//Register 6: Deemphasize filter and Volume ramp rate
#define R6_DEFAULT                  0b01001010

#define R6_DEEMPH_SEL_48K           0b10
#define R6_DEEMPH_SEL_44_1K         0b01
#define R6_DEEMPH_SEL_32K           0b00 // default

#define R6_AUTO_DEEMPH_DISABLE      0b0 // default
#define R6_AUTO_DEEMPH_ENABLE       0b1

#define R6_DEEMPH_DISABLE           0b00 // default
#define R6_DEEMPH_ENABLE            0b01

typedef union {
    struct {
        B volume_rate :3;
        B reserved :1;
        B deemph_sel :2;
        B deemph_enable :1;
        B auto_deemph :1;
    };
    B byte;
} R6_DEEMPH_FILTER_VOL_RAMP_RATE;

// Register 7: Filter configuration and system mute.
#define R7_DEFAULT                                  0b01000000

#define R7_F_SHAPE_BRICKWALL                        0b111
#define R7_F_SHAPE_HYBRID_FAST_RO_MIN_PHASE         0b110
#define R7_F_SHAPE_APODIZING_FAST_RO_LINEAR_PHASE   0b100
#define R7_F_SHAPE_SLOW_RO_MINIMUM_PHASE            0b011
#define R7_F_SHAPE_FAST_RO_MINIMUM_PHASE            0b010 // default
#define R7_F_SHAPE_SLOW_RO_LINEAR_PHASE             0b001
#define R7_F_SHAPE_FAST_RO_LINEAR_PHASE             0b000

#define R7_IIR_BW_70K                               0b11
#define R7_IIR_BW_60K                               0b10
#define R7_IIR_BW_50K                               0b01
#define R7_IIR_BW_47K                               0b00 // default

#define R7_SYSTEM_MUTE                              0b1
#define R7_SYSTEM_NORMAL_OPERATION                  0b0

typedef union {
    struct {
        B mute :1;
        B iir_bw :2;
        B reserved :2;
        B filter_shape :3;
    };
    B byte;
} R7_FILTER_BW_SYSTEM_MUTE;

// Register 8: GPIO 1-2 configuration
#define R8_DEFAULT  0b10001000

typedef union {
    struct {
        B gpio1_cfg :4;
        B gpio2_cfg :4;
    };
    B byte;
} R8_GPIO_1_2_CONFIG;

// Register 9: GPIO 3-4 configuration
#define R9_DEFAULT  0b10001000

typedef union {
    struct {
        B gpio3_cfg :4;
        B gpio4_cfg :4;
    };
    B byte;
} R9_GPIO_3_4_CONFIG;

// GPIO configurable states
#define GPIO_OUT_AUTOMUTE_STATUS        0
#define GPIO_OUT_LOCK_STATUS            1
#define GPIO_OUT_VOLUME_MIN             2
#define GPIO_OUT_CLK                    3
#define GPIO_OUT_AUTOMUTE_LOCK_INTERUPT 4
#define GPIO_OUT_ADC_CLK                5
// state 6 is reserved - so it is missing
#define GPIO_OUT_LOW                    7
#define GPIO_IN_STANDARD_INPUT          8
#define GPIO_IN_INPUT_SELECT            9
#define GPIO_IN_MUTE_ALL                10
// state 11 is reserved - so it is missing
// state 12 is reserved - so it is missing
#define GPIO_IN_ADC_INPUT               13
#define GPIO_OUT_SOFT_START_COMPLETE    14
#define GPIO_OUT_HIGH                   15

// Register 10: Master Mode and Sync Configuration
#define R10_DEFAULT                 0b00000000

#define R10_MASTER_MODE_ENABLED     0b1
#define R10_MASTER_MODE_DISABLED    0b0 // default

#define R10_MASTER_DIV_BY_2         0b00 // default
#define R10_MASTER_DIV_BY_4         0b01
#define R10_MASTER_DIV_BY_8         0b10
#define R10_MASTER_DIV_BY_16        0b11

#define R10_128FS_MODE_ENABLED      0b1
#define R10_128FS_MODE_DISABLED     0b0 // default

#define R10_LOCK_ON_EDGES_16384     0
#define R10_LOCK_ON_EDGES_8192      1
#define R10_LOCK_ON_EDGES_5461      2
#define R10_LOCK_ON_EDGES_4096      3
#define R10_LOCK_ON_EDGES_3276      4
#define R10_LOCK_ON_EDGES_2730      5
#define R10_LOCK_ON_EDGES_2340      6
#define R10_LOCK_ON_EDGES_2048      7
#define R10_LOCK_ON_EDGES_1820      8
#define R10_LOCK_ON_EDGES_1638      9
#define R10_LOCK_ON_EDGES_1489      10
#define R10_LOCK_ON_EDGES_1365      11
#define R10_LOCK_ON_EDGES_1260      12
#define R10_LOCK_ON_EDGES_1170      13
#define R10_LOCK_ON_EDGES_1092      14
#define R10_LOCK_ON_EDGES_1024      15

typedef union {
    struct {
        B lock_speed :4;
        B fs128_mode :1;
        B master_div :2;
        B master_mode :1;
    };
    B byte;
} R10_MASTER_MODE_SYNC;

// Register 11: SPDIF MUX and GPIO Inversion
#define R11_DEFAULT             0b00000000

#define R11_SPDIF_SEL_DATA_CLK  0
#define R11_SPDIF_SEL_DATA1     1
#define R11_SPDIF_SEL_DATA2     2
#define R11_SPDIF_SEL_DATA3     3
#define R11_SPDIF_SEL_DATA4     4
#define R11_SPDIF_SEL_DATA5     5
#define R11_SPDIF_SEL_DATA6     6
#define R11_SPDIF_SEL_DATA7     7
#define R11_SPDIF_SEL_DATA8     8
#define R11_SPDIF_SEL_GPIO1     9
#define R11_SPDIF_SEL_GPIO2     10
#define R11_SPDIF_SEL_GPIO3     11
#define R11_SPDIF_SEL_GPIO4     12

#define R11_GPIO_OUTPUT_NORMAL  0b0 // default
#define R11_GPIO_OUTPUT_INVERT  0b1

typedef union {
    struct {
        B invert_gpio1 :1;
        B invert_gpio2 :1;
        B invert_gpio3 :1;
        B invert_gpio4 :1;
        B spdif_sel :4;
    };
    B byte;
} R11_SPDIF_MUX_GPIO_INVERT;

// Register 12: Jitter Eliminator / DPLL bandwidth
#define R12_DEFAULT 	0b01010101

typedef union {
    // each register: 0 off - 1 lowest - 15 highest
    struct {
        B dpll_bw_dsd :4;
        B dpll_bw_serial :4;
    };
    B byte;
} R12_JE_DPLL_BW;

// Register 13: Jitter Eliminator, DPLL configuration,
// and THD compensation Enable
// This one is mysterious - because of the large reserved block
#define R13_DEFAULT                     0b00100000

#define R13_NS_DITHER_ENABLED           0b0 // default
#define R13_NS_DITHER_DISABLED          0b1

#define R13_THD_COMP_ENABLED            0b0 // default
#define R13_THD_COMP_DISABLED           0b1

#define R13_JITTER_ELIMINATOR_DISABLED  0b0
#define R13_JITTER_ELIMINATOR_ENABLED   0b1 // default

typedef union {
    struct {
        B reserved :5;
        B jitter_eliminator_enable :1;
        B thd_comp_enable :1;
        B ns_dither_enable :1;
    };
    B byte;
} R13_JE_THD_COMP_CONFIG;

// Register 14: Soft Start Configuration
#define R14_DEFAULT                             0b10001010

#define R14_SOFT_START_TO_GND                   0
#define R14_SOFT_START_TO_HALF_AVCC             1 // default

#define R14_SOFT_STOP_TO_GND_ON_UNLOCK_ENABLE   1
#define R14_SOFT_STOP_TO_GND_ON_UNLOCK_DISABLE  0 // default

typedef union {
    struct {
        // time(s) = 4096 * ((2 * (soft_start_time + 1)) / MCLK)
        B soft_start_time :5;
        B reserved :1;
        B auto_soft_stop_on_unlock :1;
        B soft_start :1;
    };
    B byte;
} R14_SOFT_START_CONFIG;

// Register 15: GPIO Input Selection and Volume Configuration
#define R15_DEFAULT                         0b00001001

#define R15_LATCH_VOLUME_DISABLED           0b0
#define R15_LATCH_VOLUME_ENABLED            0b1 // default

#define R15_USE_ONLY_CH1_VOLUME_DISABLED    0b0 // default
#define R15_USE_ONLY_CH1_VOLUME_ENABLED     0b1

#define R15_STEREO_MODE_DISABLED            0b0 // default
#define R15_STEREO_MODE_ENABLED             0b1

typedef union {
    struct {
        B latch_vol :1;
        B use_only_ch1_vol :1;
        B stereo_mode :1;
        B reserved :1;
        B gpio1_input_select :2;
        B gpio2_input_select :2;
    };
    B byte;
} R15_GPIO_INPUT_SEL_VOLUME_CONFIG;

// Registers 16-23 are Volume 1-8 respectively 0 to -127.5db .5db step
// Registers 24-27 are Master Trim 32 bit signed value
// Registers 28-29 2nd order THD compensation coefficient 16 bits signed
// Registers 30-31 3rd order THD compensation coefficient 16 bits signed
// Both THD compensation coefficients default to zero

// Register 32: Programmable FIR RAM Address
# define R32_DEFAULT    0b00000000

# define R32_STAGE_1    0b0 // default
# define R32_STAGE_2    0b1

typedef union {
    struct {
        B coeff_addr :7;
        B coeff_stage :1;
    };
    B byte;
} R32_PROGRAMMABLE_FIR_CONFIG;

// Registers 33-36 hold the 32 bit signed coefficient
// which will be written to the address defined by Register 32

typedef union {
    struct {
        B prog_en :1;
        B prog_we :1;
        B stage2_even :1;
        B prog_ext :1;
        B filter_length :1;
        B reserved :2;
        B bypass_osf :1;
    };
    B byte;
} R37_PROGRAMMABLE_FIR_CONFIG;

#define R37_DEFAULT                 0b00000000

#define R37_OSF_ENABLED             0b0 // default
#define R37_OSF_DISABLED            0b1

#define R37_FILTER_LENGTH_128       0b0 // default
#define R37_FILTER_LENGTH_256       0b1

#define R37_PROG_EXT_TO_127         0b0 // default
#define R37_PROG_EXT_TO_255         0b1

#define R37_STAGE2_SINE             0b0 // default
#define R37_STAGE2_COSINE           0b1

#define R37_PROG_WRITE_DISABLED     0b0 // default
#define R37_PROG_WRITE_ENABLED      0b1

#define R37_PROGRAM_DISABLE         0b0 // default
#define R37_PROGRAM_ENABLE          0b1

// Register 38 - 41 are channel mapping
// Register 38 maps DAC 1/2
// Register 39 maps DAC 3/4
// Register 40 maps DAC 5/6
// Register 41 maps DAC 7/8
#define R38_41_INPUT_1 0
#define R38_41_INPUT_2 1
#define R38_41_INPUT_3 2
#define R38_41_INPUT_4 3
#define R38_41_INPUT_5 4
#define R38_41_INPUT_6 5
#define R38_41_INPUT_7 6
#define R38_41_INPUT_8 7

#define R38_DEFAULT     0b00010000
#define R39_DEFAULT     0b00110010
#define R40_DEFAULT     0b01010100
#define R41_DEFAULT     0b01110110

typedef union {
    struct {
        B odd :4;
        B even :4;
    };
    B byte;
} R38_41_CHANNEL_MAPPING;

// Registers 42-45 are the 32bit NCO ratio - see the datasheet
// Registers 46-52 are the ADC settings - see the datasheet
// Register 53 is reserved
// Register 54 is reserved
// Registers 55-56 are reserved (but must be related 16 bit value)
// Registers 57-61 are reserved and look interesting...
// Register 62 allows adding +18db gain to DACs after volume control

// Register 63: Auto Calibration - See data sheet for usage
#define R63_DEFAULT =0b00000010

#define R63_CALIBRATION_DISABLED        0b0
#define R63_CALIBRATION_ENABLED         0b1
#define R63_CALIBRATION_USE_ADC1_GPIO2  0b0
#define R63_CALIBRATION_USE_ADC2_GPIO1  0b1
#define R63_CALIBRATION_LATCH_DISABLED  0b0
#define R63_CALIBRATION_LATCH_ENABLED   0b1

typedef union {
    struct {
        B reserved :5;
        B latch :1;
        B select :1;
        B enable :1;
    };
    B byte;
} R63_AUTO_CALIBRATE;

// Register 64: Chip ID and Status - READ ONLY
#define R64_LOCK_STATUS_UNLOCKED    0b0
#define R64_LOCK_STATUS_LOCKED      0b1
#define R64_AUTOMUTE_INACTIVE       0b0
#define R64_AUTOMUTE_ACTIVE         0b1

typedef union {
    struct {
        B lock_status :1;
        B automute_status :1;
        B chip_id :6;
    };
    B byte;
} R64_CHIP_ID_STATUS;

// Register 65: GPIO READBACK - READ ONLY
typedef union {
    struct {
        B gpio1 :1;
        B gpio2 :1;
        B gpio3 :1;
        B gpio4 :1;
        B reserved :4;
    };
    B byte;
} R65_GPIO_READBACK;

// Registers 66-69 are read only and contain the 32bit DPLL number
// FSR = (dpll_number * fmck) / 4294967296

// Registers 70-93 are the read only SPDIF status and User status
// see the data sheet

// Registers 94-99 are reserved

// Register 100: Input status - READ ONLY
typedef union {
    struct {
        B dsd_is_valid :1;
        B i2s_is_valid :1;
        B spdif_is_valid :1;
        B dop_is_valid :1;
        B reserved :4;
    };
    B byte;
} R100_INPUT_STATUS;



#endif /* ES9028_38_H_ */

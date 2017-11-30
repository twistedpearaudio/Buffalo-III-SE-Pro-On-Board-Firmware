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
#define R0_DEFAULT 		0b00000000

// System Registers

#define R0_CLOCK_GEAR_DIV_1 	0b00
#define R0_CLOCK_GEAR_DIV_2 	0b01
#define R0_CLOCK_GEAR_DIV_4 	0b10
#define R0_CLOCK_GEAR_DIV_8 	0b11

#define R0_OSC_DRV_OFF		0b0000
#define R0_OSC_DRV_25PCT	0b1110
#define R0_OSC_DRV_50PCT	0b1100
#define R0_OSC_DRV_75PCT	0b1000
#define R0_OSC_DRV_FULL		0b0000

typedef union {
	struct {
		B soft_reset :1;
		B reserved :1;
		B clk_gear :2;
		B osc_drv :4;
	};
	B byte;
} R0_SYSTEM;

#define R1_DEFAULT 		0b00001100
// Input Selection Registers
#define R1_AUTO_SELECT_ALL			0b11
#define R1_AUTO_SELECT_SPDIF_SERIAL	0b10
#define R1_AUTO_SELECT_DSD_SERIAL	0b01
#define R1_AUTO_SELECT_DISABLE		0b00

#define R1_INPUT_SELECT_DSD		0b11
#define R1_INPUT_SELECT_SPDIF	0b01
#define R1_INPUT_SELECT_SERIAL	0b00

#define R1_SPDIF_VALID_MUTE 	0b0
#define R1_SPDIF_VALID_IGNORE 	0b1

#define R1_SPDIF_DATA_MUTE 		0b0
#define R1_SPDIF_DATA_IGNORE 	0b1

#define R1_SPDIF_BITS_USER		0b1
#define R1_SPDIF_BITS_STATUS	0b0

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

#define R2_DEFAULT		0b00111100

#define R2_AUTOMUTE_CONFIG_MUTE_THEN_GND 	0b11
#define R2_AUTOMUTE_CONFIG_GND 				0b10
#define R2_AUTOMUTE_CONFIG_MUTE 			0b01
#define R2_AUTOMUTE_CONFIG_NORMAL_OPERATION 0b00

// Note Serial length is almost always 32 - Serial bits can almost always be 32 as well for I2S.
// Actual size of the word
#define R2_SERIAL_BITS_32 0b11
#define R2_SERIAL_BITS_24 0b01
#define R2_SERIAL_BITS_16 0b00

// DATA_CLK pulses per word
#define R2_SERIAL_LENGTH_32 0b11
#define R2_SERIAL_LENGTH_24 0b01
#define R2_SERIAL_LENGTH_16 0b00

#define R2_SERIAL_MODE_RJ  	0b11
#define R2_SERIAL_MODE_LJ  	0b01
#define R2_SERIAL_MODE_I2S  0b00

typedef union {
	struct {
		B serial_mode :2;
		B serial_length :2;
		B serial_bits :2;
		B automute_config :2;
	};
	B byte;
} R2_SERIAL_DATA_AUTOMUTE_CONFIG;

// Register 3 is reserved

#define R3_DEFAULT		0b00000000 // This is a reserved register
#define R4_DEFAULT		0b00000000

typedef union {
	B automute_time;
	B byte;
} R4_AUTOMUTE_TIME;

#define R5_DEFAULT		0b01110010

typedef union {
	struct {
		B automute_level :7;
		B reserved :1;
	};
	B byte;
} R5_AUTOMUTE_LEVEL;

#define R6_DEFAULT		0b01001010

#define R6_DEEMPH_SEL_48K 	0b10
#define R6_DEEMPH_SEL_44_1K 0b01
#define R6_DEEMPH_SEL_32K 	0b00

#define R6_AUTO_DEEMPH_DISABLE 	0b00
#define R6_AUTO_DEEMPH_ENABLE 	0b01

#define R6_DEEMPH_BYPASS_DISABLE 	0b01
#define R6_DEEMPH_BYPASS_ENABLE 	0b00

typedef union {
	struct {
		B volume_rate :3;
		B reserved :1;
		B deemph_sel :2;
		B deemph_bypass :1;
		B auto_deemph :1;
	};
	B byte;
} R6_DEEMPH_FILTER_VOL_RAMP_RATE;

#define R7_DEFAULT 		0b01000000

#define R7_FILTER_SHAPE_BRICKWALL 						0b111
#define R7_FILTER_SHAPE_HYBRID_FAST_RO_MIN_PHASE 			0b110
#define R7_FILTER_SHAPE_APODIZING_FAST_RO_LINEAR_PHASE 	0b100
#define R7_FILTER_SHAPE_SLOW_RO_MINIMUM_PHASE 			0b011
#define R7_FILTER_SHAPE_FAST_RO_MINIMUM_PHASE 			0b010
#define R7_FILTER_SHAPE_SLOW_RO_LINEAR_PHASE 			0b001
#define R7_FILTER_SHAPE_FAST_RO_LINEAR_PHASE 			0b000

#define R7_IIR_BW_70K 0b11
#define R7_IIR_BW_60K 0b10
#define R7_IIR_BW_50K 0b01
#define R7_IIR_BW_47K 0b00

#define R7_SYSTEM_MUTE  				0b1
#define R7_SYSTEM_NORMAL_OPERATION	0b0

typedef union {
	struct {
		B mute :1;
		B iir_bw :2;
		B reserved :2;
		B filter_shape :3;
	};
	B byte;
} R7_FILTER_BW_SYSTEM_MUTE;

#define R8_DEFAULT 		0b10001000

#define GPIO_OUT_AUTOMUTE_STATUS 		0
#define GPIO_OUT_LOCK_STATUS				1
#define GPIO_OUT_VOLUME_MIN				2
#define GPIO_OUT_CLK						3
#define GPIO_OUT_AUTOMUTE_LOCK_INTERUPT	4
#define GPIO_OUT_ADC_CLK					5
#define GPIO_OUT_LOW						7
#define GPIO_IN_STANDARD_INPUT		 	8
#define GPIO_IN_INPUT_SELECT		 		9
#define GPIO_IN_MUTE_ALL		 			10
#define GPIO_IN_ADC_INPUT				13
#define GPIO_OUT_SOFT_START_COMPLETE		14
#define GPIO_OUT_HIGH					15

typedef union {
	struct {
		B gpio1_cfg :4;
		B gpio2_cfg :4;
	};
	B byte;
} R8_GPIO_1_2_CONFIG;

#define R9_DEFAULT 	0b10001000

typedef union {
	struct {
		B gpio3_cfg :4;
		B gpio4_cfg :4;
	};
	B byte;
} R9_GPIO_3_4_CONFIG;

#define R10_DEFAULT 	0b00000000

#define R10_MASTER_MODE_ENABLED 		0b1
#define R10_MASTER_MODE_DISABLED 	0b0

#define R10_MASTER_DIV_BY_2			0b00
#define R10_MASTER_DIV_BY_4			0b01
#define R10_MASTER_DIV_BY_8			0b10
#define R10_MASTER_DIV_BY_16			0b11

#define R10_128FS_MODE_ENABLED 		0b1
#define R10_128FS_MODE_DISABLED 		0b0

#define R10_LOCK_ON_EDGES_16384		0
#define R10_LOCK_ON_EDGES_8192		1
#define R10_LOCK_ON_EDGES_5461		2
#define R10_LOCK_ON_EDGES_4096		3
#define R10_LOCK_ON_EDGES_3276		4
#define R10_LOCK_ON_EDGES_2730		5
#define R10_LOCK_ON_EDGES_2340		6
#define R10_LOCK_ON_EDGES_2048		7
#define R10_LOCK_ON_EDGES_1820		8
#define R10_LOCK_ON_EDGES_1638		9
#define R10_LOCK_ON_EDGES_1489		10
#define R10_LOCK_ON_EDGES_1365		11
#define R10_LOCK_ON_EDGES_1260		12
#define R10_LOCK_ON_EDGES_1170		13
#define R10_LOCK_ON_EDGES_1092		14
#define R10_LOCK_ON_EDGES_1024		15


typedef union {
	struct {
		B lock_speed :4;
		B fs128_mode :1;
		B master_div :2;
		B master_mode :1;
	};
	B byte;
} R10_MASTER_MODE_SYNC;

#define R11_DEFAULT 	0b00000000

#define R11_SPDIF_SEL_DATA_CLK 	0
#define R11_SPDIF_SEL_DATA1 		1
#define R11_SPDIF_SEL_DATA2 		2
#define R11_SPDIF_SEL_DATA3 		3
#define R11_SPDIF_SEL_DATA4 		4
#define R11_SPDIF_SEL_DATA5 		5
#define R11_SPDIF_SEL_DATA6 		6
#define R11_SPDIF_SEL_DATA7 		7
#define R11_SPDIF_SEL_DATA8 		8
#define R11_SPDIF_SEL_GPIO1 		9
#define R11_SPDIF_SEL_GPIO2 		10
#define R11_SPDIF_SEL_GPIO3 		11
#define R11_SPDIF_SEL_GPIO4 		12

#define R11_GPIO_OUTPUT_NORMAL	0
#define R11_GPIO_OUTPUT_INVERT	1

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

#define R12_DEFAULT 	0b01010101

typedef union {
	// each register: 0 off - 1 lowest - 15 highest
	struct {
		B dpll_bw_dsd :4;
		B dpll_bw_serial :4;
	};
	B byte;
} R12_JE_DPLL_BW;

#define R13_DEFAULT 	0b00100000

#define R13_NS_DITHER_ENABLED			0
#define R13_NS_DITHER_DISABLED			1

#define R13_THD_COMP_ENABLED				0
#define R13_THD_COMP_DISABLED			1

#define R13_JITTER_ELIMINATOR_ENABLED	1
#define R13_JITTER_ELIMINATOR_DISABLED	0


typedef union {
	struct {
		B reserved :5;
		B jitter_eliminator_enable :1;
		B thd_comp_enable :1;
		B ns_dither_enable :1;
	};
	B byte;
} R13_JE_THD_COMP_CONFIG;


#define R14_DEFAULT 	0b10001010
#define R14_SOFT_START_TO_GND 		0
#define R14_SOFT_START_TO_HALF_AVCC 1

#define R14_SOFT_STOP_TO_GND_ON_UNLOCK_ENABLE 	1
#define R14_SOFT_STOP_TO_GND_ON_UNLOCK_DISABLE 	0

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

#define R15_DEFAULT 	0b00001001

#define R15_LATCH_VOLUME_ENABLED	1
#define R15_LATCH_VOLUME_DISABLED	0

#define R15_USE_ONLY_CH1_VOLUME_DISABLED	0
#define R15_USE_ONLY_CH1_VOLUME_ENABLED		1

#define R15_STEREO_MODE_ENABLED	1
#define R15_STEREO_MODE_DISABLED	0

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

// Registers 16-23 are Volume 1 - 8 respectively 0 to -127.5db in .5db steps
// Registers 24-27 are Master Trim 32 bit signed value

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

#define R37_DEFAULT				0b00000000
#define R37_OSF_ENABLED  		0
#define R37_OSF_DISABLED  		1
#define R37_FILTER_LENGTH_128	0
#define R37_FILTER_LENGTH_256	1
#define R37_PROG_EXT_TO_127		0
#define R37_PROG_EXT_TO_255		1
#define R37_STAGE2_SINE			0
#define R37_STAGE2_COSINE		1
#define R37_PROG_WRITE_ENABLED	1
#define R37_PROG_WRITE_DISABLED	0
#define R37_PROGRAM_ENABLE		1
#define R37_PROGRAM_DISABLE		0



// TODO: Add the rest of the registers

#endif /* ES9028_38_H_ */

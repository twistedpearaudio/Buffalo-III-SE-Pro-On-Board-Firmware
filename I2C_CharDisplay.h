/*
 * I2C_CharDisplay_PortExpander.h
 *
 *  Maps the I/O outputs for the I2C Character Display Port Expander
 *
 *
 *  Created on: Apr 22, 2018
 *      Author: rwhite
 */

#include "inttypes.h"
#ifndef I2C_CHARDISPLAY_H_
#define I2C_CHARDISPLAY_H_
typedef uint8_t B;

#define LCD_PE_ADDRESS                       0x4E
// Commands
#define LCD_CLEAR_DISPLAY   0x01
#define LCD_RETURN_HOME     0x02
#define LCD_ENTRY_MODE_SET  0x04
#define LCD_DISPLAY_CONTROL 0x08
#define LCD_CURSOR_SHIFT    0x10
#define LCD_FUNCTION_SET    0x20
#define LCD_SET_CGRAM_ADDR  0x40
#define LCD_SET_DDRAM_ADDR  0x80

// flags for entry mode
#define LCD_ENTRY_RIGHT             0x00
#define LCD_ENTRY_LEFT              0x02
#define LCD_ENTRY_SHIFT_INCREMENT   0x01
#define LCD_ENTRY_SHIFT_DECREMENT   0x00

// flags for display on/off control
#define LCD_DISPLAY_ON      0x04
#define LCD_DISPLAY_OFF     0x00
#define LCD_CURSOR_ON       0x02
#define LCD_CURSOR_OFF      0x00
#define LCD_BLINK_ON        0x01
#define LCD_BLINK_OFF       0x00

// flags for display/cursor shift
#define LCD_DISPLAY_MOVE    0x08
#define LCD_CURSOR_MOVE     0x00
#define LCD_MOVE_RIGHT      0x04
#define LCD_MOVE_LEFT       0x00

// flags for function set
#define LCD_8_BIT_MODE      0x10
#define LCD_4_BIT_MODE      0x00
#define LCD_2_LINE          0x08
#define LCD_1_LINE          0x00
#define LCD_5x10_DOTS       0x04
#define LCD_5x8_DOTS        0x00

// flags for back light control
#define LCD_BACK_LIGHT      0x08
#define LCD_NO_BACK_LIGHT   0x00

#define LCD_EN              0b00000100
#define LCD_RW              0b00000010
#define LCD_RS              0b00000001

#define LCD_COMMAND_MODE    LCD_BACK_LIGHT
#define LCD_DATA_MODE       LCD_BACK_LIGHT | LCD_RS

void lcd_strobe(uint8_t data);
void lcd_write_4_bits(uint8_t data);
void lcd_write(uint8_t data, uint8_t mode);
void lcd_write_command(uint8_t data);
void lcd_write_data(uint8_t data);
void lcd_print(uint8_t line, uint8_t *text);
void lcd_init();

#endif /* I2C_CHARDISPLAY_H_ */

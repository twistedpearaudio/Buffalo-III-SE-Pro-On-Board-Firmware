/*
 * I2C_CharDisplay.c
 *
 *  Created on: Apr 23, 2018
 *      Author: rwhite
 */
#include <util/delay.h>
#include <avr/io.h>
#include <stdint.h>

#include "USI_I2C_Master.h"
#include "I2C_CharDisplay.h"

void lcd_device_write(uint8_t data) {
    i2c_start_wait(LCD_PE_ADDRESS);
    i2c_write(data);
    i2c_stop();
}
void lcd_strobe(uint8_t data) {
    lcd_device_write(data | LCD_EN);
    _delay_us(500);
    lcd_device_write(data & ~LCD_EN);
    _delay_us(500);
}
void lcd_write_4_bits(uint8_t data) {
    lcd_device_write(data);
    lcd_strobe(data);
}
void lcd_write(uint8_t data, uint8_t mode) {
    lcd_write_4_bits((data & 0xF0) | mode);
    lcd_write_4_bits(((data << 4) & 0XF0) | mode);
}
void lcd_write_command(uint8_t data) {
    lcd_write(data,LCD_COMMAND_MODE);
}
void lcd_write_data(uint8_t data) {
    lcd_write(data,LCD_DATA_MODE);
}
void lcd_print(uint8_t line, uint8_t *text) {
    if (line == 1)
        lcd_write_command(0x80);
    else if (line == 2)
        lcd_write_command(0xC0);
    else if (line == 3)
        lcd_write_command(0x94);
    else if (line == 4)
        lcd_write_command(0xD4);
    while (*text) {
        lcd_write_data(*text++);
    }
}
void lcd_init() {
    _delay_ms(50);
    lcd_write_4_bits(0x30);
    lcd_write_4_bits(0x30);
    lcd_write_4_bits(0x30);
    lcd_write_4_bits(0x20);
    lcd_write_command(LCD_FUNCTION_SET | LCD_2_LINE | LCD_5x10_DOTS | LCD_4_BIT_MODE);
    lcd_write_command(LCD_DISPLAY_CONTROL | LCD_DISPLAY_ON);
    lcd_write_command(LCD_CLEAR_DISPLAY);
    lcd_write_command(LCD_ENTRY_MODE_SET | LCD_ENTRY_LEFT);
    _delay_ms(20);
}



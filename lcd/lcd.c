/*
 * PIC18F2550 Libraries - Alphanumeric Liquid Crystal Display (LCD)
 *
 * Library for 1602 LCDs.
 *
 * @author Gutierrez PS
 * @see https://github.com/gutierrezps/PIC18F2550_Libraries
 *
 */

#include <xc.h>
#include "lcd.h"
#include "print.h"

#define LCD_CURSOR_ON       0x02
#define LCD_CURSOR_BLINK    0x01


void lcd_pulse_en() {
    __delay_us(1);
    LCD_EN = 1;
    __delay_us(1);
    LCD_EN = 0;
    __delay_us(40);
}

/**
 * Sends a byte to the LCD (4 bit mode), using RB4-RB7 as data pins.
 *
 * @param data
 */
void lcd_send(unsigned char data) {
    LATB = (data & 0xF0) | (LATB & 0x0F);
    lcd_pulse_en();
    data <<= 4;
    LATB = (data & 0xF0) | (LATB & 0x0F);
    lcd_pulse_en();
}


/**
 * Clears the LCD and returns the cursor to position (0, 0).
 *
 * Takes 2 ms to complete.
 */
void lcd_clear(void) {
    LCD_RS = 0;
    lcd_send(0x01);
    __delay_ms(2);
}


/**
 * Initializes the LCD, using RB4-RB7 as data bits.
 */
void lcd_begin(void) {
    TRISB &= 0x0F;       // using pins RB7-RB4 for data
    LATB &= 0x0F;
    LCD_EN_TRIS = 0;
    LCD_EN = 0;
    LCD_RS_TRIS = 0;
    LCD_RS = 0;
    __delay_ms(100);    // startup time

    LCD_RS = 0;         // command mode

    // init sequence, according to Hitachi HD44780 datasheet
    LATB = 0x30 | (LATB & 0x0F);
    lcd_pulse_en();
    __delay_ms(5);

    lcd_pulse_en();
    __delay_ms(5);

    lcd_pulse_en();
    __delay_us(100);

    LATB = 0x20 | (LATB & 0x0F);
    lcd_pulse_en();
    __delay_us(100);

    // display configuration

    // function set: 2 lines, 5x8 dot matrix
    lcd_send(0x28);

    // display on and cursor options
    lcd_send(0x0C | LCD_CURSOR_ON | LCD_CURSOR_BLINK);

    lcd_clear();

    // entry mode set: cursor moves to right, no shift
    lcd_send(0x06);
}


/**
 * Writes a single character to the LCD.
 */
void lcd_write(char c) {
    LCD_RS = 1;
    lcd_send(c);
}


/**
 * Changes the cursor position in the LCD screen.
 *
 * @param row   starting at 0
 * @param col   starting at 0
 */
void lcd_set_cursor(char row, char col) {
    col &= 0x0F;
    char addr = col;

    if (row == 1) {
        addr |= 0x40;
    }
    else if (row == 2) {
        addr |= 0x10;
    }
    else if (row == 3) {
        addr |= 0x50;
    }

    LCD_RS = 0;
    lcd_send(0x80 | addr);
}


void lcd_print_str(const char *str) {
    print_str(str, lcd_write);
}


void lcd_print_int(int number) {
    print_int(number, lcd_write);
}


void lcd_print_float(float number, char decimals) {
    print_float(number, decimals, lcd_write, lcd_print_int);
}

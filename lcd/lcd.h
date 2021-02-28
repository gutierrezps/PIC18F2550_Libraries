/*
 * PIC18F2550 Libraries - Alphanumeric Liquid Crystal Display (LCD)
 *
 * Library for 1602 LCDs.
 *
 * Schematic:
 * PIC     LCD
 * RB7 --- D7
 * RB6 --- D6
 * RB5 --- D5
 * RB4 --- D4
 *         D3~D0: unconnected
 * RB3 --- EN
 * GND --- RW
 * RB2 --- RS
 * VCC --- VDD
 * GND --- VSS
 * pot --- VEE
 *
 * @author Gutierrez PS
 * @see https://github.com/gutierrezps/PIC18F2550_Libraries
 *
 */

#ifndef LCD_H
#define	LCD_H

#include <xc.h>
#include "config.h"

#define LCD_EN      LATBbits.LATB2
#define LCD_EN_TRIS TRISBbits.TRISB2
#define LCD_RS      LATBbits.LATB3
#define LCD_RS_TRIS TRISBbits.TRISB3


/**
 * Initializes the LCD, using RB4-RB7 as data bits.
 */
void lcd_begin(void);


/**
 * Clears the LCD and returns the cursor to position (0, 0).
 *
 * Takes 2 ms to complete.
 */
void lcd_clear(void);



/**
 * Writes a single character to the LCD.
 */
void lcd_write(char c);


/**
 * Changes the cursor position in the LCD screen.
 *
 * @param row   starting at 0
 * @param col   starting at 0
 */
void lcd_set_cursor(char row, char col);


void lcd_print_str(const char *str);


void lcd_print_int(int number);


void lcd_print_float(float number, char decimals);

#endif	/* LCD_H */

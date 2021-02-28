/*
 * PIC18F2550 Libraries - Alphanumeric Liquid Crystal Display (LCD)
 *
 * Prints numbers and strings at startup.
 *
 * Suggested schematic:
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
 * pot is a display contrast adjust potentiometer connected as a
 * voltage divider, like this:
 *
 * VDD --- pot --- VSS
 *          |
 *         VEE
 *
 * If you don't connect it, the display won't show anything. You can
 * replace it by a fixed voltage divider that outputs ~0.7V (the lower
 * the voltage, the higher is the contrast).
 *
 * Download and add "print.h" and "print.c" to the project.
 *
 * @author Gutierrez PS
 * @see https://github.com/gutierrezps/PIC18F2550_Libraries
 *
 */

#include <xc.h>
#include "config.h"
#include "print.h"
#include "lcd.h"

void main(void) {
    OSCCONbits.IRCF = 0b111;    // 8 MHz INTOSC frequency
    OSCCONbits.SCS = 0b10;      // Select INTOSC as system clock

    lcd_begin();

    lcd_print_str("Integer: ");
    lcd_print_int(32767);

    lcd_set_cursor(1, 0);
    lcd_print_str("Float: ");
    lcd_print_float(-12.34, 3);

    while (1) {

    }
}

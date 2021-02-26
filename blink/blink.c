/*
 * PIC18F2550 Examples - Blink
 *
 * Toggles output pin B7 every 1 second. Using 8 MHz internal oscillator,
 * so no external crystal is needed.
 *
 * Suggested schematic (starting from base circuit):
 * RB7 --- 1k resistor --- LED --- GND
 *
 * @author Gutierrez PS
 * @see https://github.com/gutierrezps/PIC18F2550_Examples
 *
 */

#include <xc.h>
#include "config.h"

void main(void) {
    OSCCONbits.IRCF = 0b111;    // 8 MHz INTOSC frequency
    OSCCONbits.SCS = 0b10;      // Select INTOSC as system clock

    TRISB7 = 0;     // Set B7 as output

    while (1) {
        LATB7 = 1;
        __delay_ms(1000);       // XC8 macro
        LATB7 = 0;
        __delay_ms(1000);
    }
}

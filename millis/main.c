/*
 * PIC18F2550 Libraries - millis() demonstration
 *
 * Toggles RB7 every second, using millis() function as a non-blocking
 * delay. That means you can run other tasks inside the main while loop.
 *
 * @author Gutierrez PS
 * @see https://github.com/gutierrezps/PIC18F2550_Libraries
 *
 */

#include <xc.h>
#include "config.h"
#include "millis.h"


/**
 * High-priority interrupt handling routine. Required for millis() to work.
 */
void __interrupt(high_priority) isr_hp() {
    MILLIS_TMR0_ISR();

    // add other high-priority interrupts handling below
    // ...
}


void main() {
    OSCCONbits.IRCF = 0b111;    // 8 MHz INTOSC frequency
    OSCCONbits.SCS = 0b10;      // Select INTOSC as system clock

    millis_begin();

    TRISB7 = 0;

    unsigned long last_toggle_millis = millis();

    while (1) {
        if (millis() - last_toggle_millis > 1000) {
            last_toggle_millis = millis();

            LATB7 = ~LATB7;
        }

        // add other tasks below
        // ...
    }
}
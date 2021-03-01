/*
 * PIC18F2550 Libraries - Millis
 *
 * Arduino-like millis() function, for non-blocking delays.
 *
 * @author Gutierrez PS
 * @see https://github.com/gutierrezps/PIC18F2550_Libraries
 *
 */

#include <xc.h>
#include "millis.h"

unsigned long g_millis_counter = 0;


void millis_begin(void) {
    g_millis_counter = 0;

    TMR0L = MILLIS_TMR0_PRELOAD;

    // 8-bit, internal clock, use 1:16 prescaler
    T0CON = 0b11000011;

    TMR0IF = 0;
    TMR0IE = 1;
    TMR0IP = 1;     // high priority TMR0 interrupt
    IPEN = 1;       // enable interrupt priority
    GIEH = 1;       // enable high-priority interrupts
}


unsigned long millis(void) {
    return g_millis_counter;
}
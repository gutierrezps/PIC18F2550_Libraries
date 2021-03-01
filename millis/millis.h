/*
 * PIC18F2550 Libraries - Millis
 *
 * Arduino-like millis() function, for non-blocking delays.
 *
 * Returns how many milliseconds elapsed since millis_begin() was called.
 * It's based on Timer0 as a high-priority interrupt, so you must
 * call millis_begin() at the very start of your code (after configuring your
 * oscillator), write an interrupt routine and add MILLIS_TMR0_ISR() macro
 * inside it. Check the main.c example file.
 *
 * As an "unsigned long", 32-bit value (per XC8 User Guide), millis() will
 * rollover (reset) after 49.7 days.
 *
 * @author Gutierrez PS
 * @see https://github.com/gutierrezps/PIC18F2550_Libraries
 *
 */

#ifndef MILLIS_H
#define MILLIS_H

#include <xc.h>


/**
 * Timer0 preload value for 1 ms interrupt, assuming an
 * 8 MHz internal clock, 8-bit counter and 1:16 prescaler
 */
#define MILLIS_TMR0_PRELOAD 131


/**
 * Macro that handles Timer0 interrupts, must be called in your
 * high-priority isr.
 */
#define MILLIS_TMR0_ISR() \
    do {\
        if (TMR0IE && TMR0IF) {\
            TMR0IF = 0;\
            TMR0 = MILLIS_TMR0_PRELOAD - TMR0;\
            ++g_millis_counter;\
        }\
    } while(0)


/**
 * DO NOT USE THIS. Use millis() function.
 *
 * Global variable that stores the current millis value. It shall not be used
 * in your code, as you might change its value accidentally.
 */
extern unsigned long g_millis_counter;


/**
 * Configures timer0 high-priority interrupt for millis().
 * Enables flags IPEN and GIEH.
 *
 * An ISR must be written and MILLIS_ISR() must be called inside it,
 * otherwise millis() won't work.
 */
void millis_begin(void);


/**
 * Returns how many milliseconds, approximately, elapsed since millis_begin()
 * was called.
 */
unsigned long millis(void);


#endif	/* MILLIS_H */
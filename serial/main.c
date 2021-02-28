/*
 * PIC18F2550 Examples - Basic Serial
 *
 * Prints a message to Serial on start-up, and then sends back
 * all data received. 57600 bps baud rate is used.
 *
 * Serial reading is not interrupt based. The PIC's input buffer has only
 * two bytes, so any data received while the buffer is full will be lost.
 *
 * Suggested schematic:
 * PIC          USB-Serial converter
 * RC6 (TX) --- RX
 * RC7 (RX) --- TX
 * GND -------- GND
 *
 * @author Gutierrez PS
 * @see https://github.com/gutierrezps/PIC18F2550_Examples
 *
 */

#include <xc.h>
#include "config.h"
#include "serial.h"


void main(void) {
   OSCCONbits.IRCF = 0b111;    // 8 MHz INTOSC frequency
   OSCCONbits.SCS = 0b10;      // Select INTOSC as system clock

   serial_begin();

   serial_print_str("Here's the minimum int: ");
   serial_print_int(-32767);

   serial_print_str("\nHere's the maximum int: ");
   serial_print_int(32767);

   serial_print_str("\nAnd here's a float: ");
   serial_print_float(12.3456, 5);

   serial_print_str("\nNow I'll echo what you say\n");

   while (1) {
       while (serial_is_available()) {
           serial_write(serial_read());
       }
   }
}

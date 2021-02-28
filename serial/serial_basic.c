/*
 * PIC18F2550 Libraries - Basic Serial
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
 * Download and add "print.h" and "print.c" to the project.
 *
 * @author Gutierrez PS
 * @see https://github.com/gutierrezps/PIC18F2550_Libraries
 *
 */

#include <xc.h>
#include "config.h"
#include "print.h"


/**
 * Initialize Serial on pins RC6 (TX) and RC7 (RX), with 57600 bps baud rate
 */
void serial_begin() {
    // Assuming 8 MHz clock speed...
    BRGH = 1;       // high speed
    BRG16 = 1;      // 16-bit BRG
    SPBRG = 34;     // 57600 bps baud rate

    SYNC = 0;       // asynchronous Serial
    SPEN = 1;       // enable Serial port
    TXCKP = 0;      // do not invert TX signal
    TXIE = 0;       // disable TX interrupt
    TX9 = 0;        // 8-bit TX data
    TXEN = 1;       // enable TX

    RXDTP = 0;      // do not invert RX signal
    RCIE = 0;       // disable RX interrupt
    RX9 = 0;        // 8-bit RX data
    CREN = 1;       // enable RX
}


/**
 * Writes a single byte to Serial.
 */
void serial_write(char c) {
    while (!TXIF) NOP();    // wait TXREG to be empty
    TXREG = c;
    NOP();
}


/**
 * Returns 1 if there's data available in the RX buffer.
 *
 * The RX buffer has only two bytes, so any data received when the buffer
 * is full will be lost, and the OERR flag will be set.
 */
char serial_is_available() {
    if (OERR) {     // clear overrun error
        CREN = 0;
        NOP();
        CREN = 1;
    }

    return RCIF;
}


/**
 * Reads a single byte from RX buffer.
 */
unsigned char serial_read() {
    return RCREG;
}


void serial_print_str(const char *str) {
    print_str(str, serial_write);
}

void serial_print_int(int number) {
    print_int(number, serial_write);
}

void serial_print_float(float number, char decimals) {
    print_float(number, decimals, serial_write, serial_print_int);
}


void main(void) {
    OSCCONbits.IRCF = 0b111;    // 8 MHz INTOSC frequency
    OSCCONbits.SCS = 0b10;      // Select INTOSC as system clock

    TRISB7 = 0;     // Set B7 as output

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

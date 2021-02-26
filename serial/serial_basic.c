/*
 * PIC18F2550 Examples - Serial basic
 *
 * Prints numbers strings to Serial on start-up, and then sends back
 * all data received. 115600 bps baud rate is used.
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


/**
 * Initialize Serial on pins RC6 (TX) and RC7 (RX), with 115200 bps baud rate
 */
void serial_begin() {
    // Assuming 8 MHz clock speed...
    BRGH = 1;       // high speed
    BRG16 = 1;      // 16-bit BRG
    SPBRG = 16;     // 115200 bps baud rate

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
void serial_write(unsigned char c) {
    while (!TXIF) NOP();    // wait TXREG to be empty
    TXREG = c;
}


/**
 * Writes each char of a null-terminated string to Serial.
 */
void serial_print_str(const char *str) {
    while (*str != '\0') {
        serial_write(*str);
        str++;
    }
}

/**
 * Prints a signed integer (between -32767 and 32767) to Serial.
 */
void serial_print_int(int number) {
    if (number == 0) {
        serial_write('0');
        return;
    }

    if (number < 0) {
        serial_write('-');
        number *= -1;
    }

    char buffer[6] = {0};
    char i = 0;

    while (number != 0 && i != 5) {
        buffer[i] = number % 10;
        number /= 10;
        ++i;
    }

    if (number != 0) {
        serial_print_str("overflow");
    }
    else {
        while (i != 0) {
            serial_write('0' + buffer[i-1]);
            --i;
        }
    }
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


void main(void) {
    OSCCONbits.IRCF = 0b111;    // 8 MHz INTOSC frequency
    OSCCONbits.SCS = 0b10;      // Select INTOSC as system clock

    TRISB7 = 0;     // Set B7 as output

    serial_begin();

    serial_print_str("Here's the minimum int: ");
    serial_print_int(-32767);

    serial_print_str("\nAnd here's the maximum int: ");
    serial_print_int(32767);

    serial_print_str("\nNow I'll echo what you say\n");

    while (1) {
        while (serial_is_available()) {
            serial_write(serial_read());
        }
    }
}

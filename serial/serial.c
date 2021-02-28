/*
 * PIC18F2550 Libraries - Serial  (57600 bps baud rate)
 *
 * @author Gutierrez PS
 * @see https://github.com/gutierrezps/PIC18F2550_Libraries
 *
 */

#include <xc.h>
#include "config.h"
#include "print.h"
#include "serial.h"


void serial_begin(void) {
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


void serial_write(char c) {
    while (!TXIF) NOP();    // wait TXREG to be empty
    TXREG = c;
    NOP();
}


char serial_is_available(void) {
    if (OERR) {     // clear overrun error
        CREN = 0;
        NOP();
        CREN = 1;
    }

    return RCIF;
}


unsigned char serial_read(void) {
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

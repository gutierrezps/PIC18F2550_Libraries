/*
 * PIC18F2550 Libraries - Serial (57600 bps baud rate)
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

#ifndef SERIAL_H
#define SERIAL_H


/**
 * Initialize Serial on pins RC6 (TX) and RC7 (RX), with 57600 bps baud rate
 */
void serial_begin(void);


/**
 * Writes a single byte to Serial.
 */
void serial_write(char c);


/**
 * Returns 1 if there's data available in the RX buffer.
 *
 * The RX buffer has only two bytes, so any data received when the buffer
 * is full will be lost, and the OERR flag will be set.
 */
char serial_is_available(void);


/**
 * Reads a single byte from RX buffer.
 */
unsigned char serial_read(void);


void serial_print_str(const char *str);

void serial_print_int(int number);

void serial_print_float(float number, char decimals);

#endif
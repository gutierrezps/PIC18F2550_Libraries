/*
 * PIC18F2550 Libraries - Print utils
 *
 * Generic print functions. Pass as a parameter the function that writes
 * a single character.
 *
 * For example: In order to print an integer (number) to the Serial port,
 * you should call:
 *
 *      print_int(number, serial_write);
 *
 * Where serial_write is the function that writes a single character to Serial.
 *
 * @author Gutierrez PS
 * @see https://github.com/gutierrezps/PIC18F2550_Libraries
 *
 */

#ifndef PRINT_H
#define	PRINT_H

/**
 * Prints a null-terminated string.
 *
 * E.g. print_str("hello", serial_write)
 *
 * @param str       string to be printed
 * @param write_fn  function that writes a single character
 */
void print_str(const char *str, void (*write_fn)(char));


/**
 * Prints a signed integer (between -32767 and 32767).
 *
 * E.g. print_int(i, serial_write)
 *
 * @param number
 * @param write_fn  function that writes a single character
 */
void print_int(int number, void (*write_fn)(char));


/**
 * Prints a floating point number.
 *
 * E.g. print_float(f, 3, serial_write, serial_print_int)
 *
 * @param number
 * @param decimals      number of decimal digits to be printed
 * @param write_fn      function that writes a single character
 * @param print_int_fn  function that writes a signed integer
 */
void print_float(float number, char decimals,
                 void (*write_fn)(char), void (*print_int_fn)(int));

#endif	/* PRINT_H */

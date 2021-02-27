/*
 * PIC18F2550 Examples - Print utils
 *
 * Generic print functions. See print.h for details.
 *
 * @author Gutierrez PS
 * @see https://github.com/gutierrezps/PIC18F2550_Examples
 *
 */

#include "print.h"

void print_str(const char *str, void (*write_fn)(char)) {
    while (*str != '\0') {
        write_fn(*str);
        ++str;
    }
}


void print_int(int number, void (*write_fn)(char)) {
    if (number == 0) {
        write_fn('0');
        return;
    }

    if (number < 0) {
        write_fn('-');
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
        write_fn('#');
    }
    else {
        while (i != 0) {
            write_fn('0' + buffer[i-1]);
            --i;
        }
    }
}

void print_float(float number, char decimals, void (*write_fn)(char), void (*print_int_fn)(int)) {
    print_int_fn((int) number);
    write_fn('.');

    if (number < 0) {
        number *= -1;
    }
    number -= (int) number;

    while (decimals != 0) {
        number *= 10;
        print_int_fn((int) number);
        number -= (int) number;
        --decimals;
    }
}

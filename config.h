/*
 * PIC18F2550 Libraries - Configuration file
 *
 * Check all available settings and values in XC8 docs (pic18_chipinfo.html).
 * It's located somewhere like C:/Program Files/Microchip/xc8/v2.32/docs.
 *
 * Attention to XC8 Compiler User Guide advice (section 5.2.5 -  Configuration
 * Bit Access):
 *
 *      All the bits in the Configuration Words should be programmed to
 *      prevent erratic program behavior. Do not leave them in their
 *      default/unprogrammed state.
 *
 * Also,
 *
 *      It is recommended that the setting-value pairs be quoted to ensure that
 *      the preprocessor does not perform macro substitution of these tokens.
 *
 * @author Gutierrez PS
 * @see https://github.com/gutierrezps/PIC18F2550_Libraries
 *
 */

#ifndef CONFIG_H
#define	CONFIG_H

// CONFIG1L
#pragma config "PLLDIV  = 1"        // No prescale (4 MHz oscillator input drives PLL directly)
#pragma config "CPUDIV  = OSC1_PLL2"    // [Primary Oscillator Src: /1][96 MHz PLL Src: /2]
#pragma config "USBDIV  = 1"        // USB clock source comes directly from the primary oscillator block with no postscale

// CONFIG1H
#pragma config "FOSC    = INTOSCIO_EC"  // Internal oscillator, port function on RA6, EC used by USB (INTIO)
#pragma config "FCMEN   = OFF"      // Fail-Safe Clock Monitor disabled

// CONFIG2L
#pragma config "PWRT    = ON"       // Power-up timer enabled
#pragma config "BOR     = OFF"      // Brown-out Reset is disabled in hardware and software
#pragma config "BORV    = 2"        // Setting 1 2.79V
#pragma config "VREGEN  = OFF"      // USB voltage regulator disabled

// CONFIG2H
#pragma config "WDT     = OFF"      // WDT is disabled (control is placed on the SWDTEN bit)
#pragma config "WDTPS   = 32768"    // Watchdog Timer Postscale 1:32768

// CONFIG3H
#pragma config "CCP2MX  = ON"       // CCP2 input/output is multiplexed with RC1
#pragma config "PBADEN  = 0"        // PORTB A/D<4:0> pins are configured as digital I/O on Reset
#pragma config "LPT1OSC = OFF"      // Timer1 configured for higher power operation
#pragma config "MCLRE   = ON"       // MCLR pin is enabled, RE3 input pin is disabled

// CONFIG4L
#pragma config "STVREN  = ON"       // Stack full/underflow will cause Reset
#pragma config "LVP     = OFF"      // Low-Voltage Programming is disabled, RB5 is an I/O pin
#pragma config "XINST   = OFF"      // Instruction set extension and Indexed Addressing mode disabled
#pragma config "DEBUG   = OFF"      // Background debugger is disabled, RB6 and RB7 are configured as general purpose I/O pins


#pragma config "CONFIG5L = 0x0F"    // Code protection disabled

#pragma config "CONFIG5H = 0xC0"    // Data EEPROM and boot block code protection disabled

#pragma config "CONFIG6L = 0x0F"    // Write protection disabled

#pragma config "CONFIG6H = 0xE0"    // Data EEPROM, boot block and configuration register write protection disabled

#pragma config "CONFIG7L = 0x0F"    // Table Read Protection disabled

#pragma config "CONFIG7H = 0x40"    // Boot Block Table Read Protection disabled


/*
 * Oscillator frequency (in Hertz) used by the system.
 *
 * Note that this macro only controls the behavior of delay macros,
 * and does not affect the device execution speed.
 */
#define _XTAL_FREQ  8000000L


#endif	/* CONFIG_H */

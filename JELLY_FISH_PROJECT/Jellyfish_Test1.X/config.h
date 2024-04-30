/*
 * config.h:        Config directives for dsPIC33CH128MP508
 *  
 * Original File:   newmainXC16.c
 * Original Author: MCSELE
 * Original Date:   Created on April 17, 2020, 1:34 PM
 * 
 * Modified by:	    Mike Boldin <mboldin@niagaracollege.ca>
 * 
 * Modification History
 * --------------------
 * 2021-10-01	(MB)	Extracted config directives from newmainXC16.c
 *                       to replace deprecated ASM "config" directives:
 *                       https://www.microchip.com/forums/m1088477.aspx
 *                      Built and tested under MPLAB X 5.30
 * 2022-01-14   (MB)    Tidied up to fit into 80-character lines;
 *                       added comments from 33CH128MP508.html
 */

// CONFIG2
#pragma config POSCMD = HS              // HS Crystal Oscillator Mode

#pragma config XTCFG = G0               // 4-8 MHz xtal

#pragma config OSCIOFNC = OFF           // Primary Oscillator Output Function 
                                        //  (OSCO functions as CLKO [FOSC/2])

#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor 
                                        //  (Both Clock Switching and  
                                        //   Fail-safe Clock Monitor are 
                                        //   disabled)

#pragma config FNOSC = PRI              // Primary Oscillator (HS) Source

#pragma config FWDTEN = ON_SW           // Watchdog Timer:
                                        //  WDT controlled via SW, 
                                        //  use WDTCON.ON bit

#pragma config JTAGEN = OFF             // JTAG is disabled

#pragma config ICS = PGD2               // ICD Communication Channel Select 
                                        //  bits (Explorer 16/32 board with 
                                        //  dsPIC33C PIM)

#pragma config IESO = ON                // Internal External Switch Over Mode 
                                        //  (IESO mode [Two-speed start-up] 
                                        //  enabled)

/* End of config.h */
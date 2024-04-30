/* 
 * File:   main.h
 * Author: MCools
 *
 * Created on December 28, 2023, 8:30 PM
 */

/*** DO NOT MODIFY CODE IN THIS FILE ***/

#include <xc.h>
#include <stdio.h>          // Required for printf()
#include <stdlib.h>

/* Clock Definitions */
#define FOSC                8000000UL   //FOSC = 8 MHZ, FOSC/2 = 4 MHZ
#define FCY                 (FOSC/2)
#include <libpic30.h>       // Req. for __delay32(), __delay_ms(), __delay_us

#include "config.h"
#include "support.h"


//// Basic Integer types
//// See MPLAB® XC16 C Compiler User?s Guide section "8.3 Integer Data Types"
//// IMPORTANT NOTE:  Unless explicity specified, all integer data types are 
////                  arithmetic type signed integers. 
//#define int8        char            //  8 bit signed (-128 to 127)
//#define int16       int             // 16 bit signed (-32768 to 32767)
//#define int32       long            // 32 bit signed (-(2^31) to (2^31)-1)
#define BYTE        unsigned int8


// Boolean Types 
// See MPLAB® XC16 C Compiler User?s Guide section "Appendix B.4 Data Type" 
// Must include 'stdbool.h' for boolean types.
#include <stdbool.h>    
#define FALSE   false
#define TRUE    true

#include "support.c"




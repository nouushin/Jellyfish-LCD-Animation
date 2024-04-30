/* 
 * File:   support.h
 * Author: MCools
 *
 * Created on December 28, 2023, 8:53 PM
 */

/*** DO NOT MODIFY CODE IN THIS FILE ***/

#define dbgBAUD             19200
#define dbgBRGVAL           ((FCY/dbgBAUD)/16)-1
#define dbgSW_DEBOUNCE_MS   250

// Macro to output to UART1 a debugging string using printf 
#define dbgPrintf(fmt, args...)     IEC0bits.U1TXIE=1; printf(fmt, ##args); printf("\r\n")

/*******************************************************************************
*                         FUNCTION PROTOTYPES                                  *
*******************************************************************************/
void PPS_ExtInt1();
void PPS_UART1();
void UART1_Init();
void dbgPause();
void dbgInit();


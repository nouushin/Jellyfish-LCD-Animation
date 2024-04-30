#ifndef LCD_H
#define	LCD_H
/* 
 * File:        LCD.h
 * Description: Library of LCD routines for the for the dsPIC33CH128MP508 on 
 *               a Microchip Explorer 16/32
 * Author:      Michael Boldin
 *              <mboldin@niagaracollege.ca>
 *
 * Modification History
 * ====================
 * Created on January 19, 2019, 2:32 PM
 * 2021-11-04   (MB)    Joined LCD_PTB.h with Microchip's
 *                       Explorer 16/32 demo code
 * 2021-11-05   (MB)    Started port and merge process;
 *                       removed hardware-specific constants;
 *                       completed port and tested
 */

/*
 *  Public Functions
 *  ================
 *  LCD_Init    Initialize the LCD I/O lines and display for normal, 
 *               4-bit operation. 
 *
 *  LCD_Char    Send a character to the LCD
 *
 *  LCD_Cmd     Send a command to the LCD
 *
 *  LCD_Clear, LCD_Home	
 *              Clear Screen and/or Move to Home (Line 1, Column 1)
 *
 *  LCD_Line1, LCD_Line2	
 *              Position cursor at start of line 1 or line 2 on the LCD
 * 
 *  LCD_ToLineCol
 *              Position cursor to any line and column
 *
 *  LCD_StringOut	
 *              Output a string to the LCD
 *
 ***************************************************************************/

/* Includes required by Microchip's functions */
#include <stdint.h>
#include <stdbool.h>

#ifdef	__cplusplus
extern "C" {
#endif

void LCD_Init(void);
void LCD_Char(unsigned char);
void LCD_Cmd(unsigned char);
void LCD_Clear(void);
void LCD_Home(void);	
void LCD_Line1(void);
void LCD_Line2(void);	
void LCD_StringOut(const char *);

#define LCD_LINES           2
#define LCD_CHARS_PER_LINE	16

void LCD_ToLineCol( int line, int col );

/*** Begin Microchip LCD H ***/

/*******************************************************************************
Copyright 2016 Microchip Technology Inc. (www.microchip.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*******************************************************************************/

/*********************************************************************
* Function: bool LCD_Initialize(void);
*
* Overview: Initializes the LCD screen.  Can take several hundred
*           milliseconds.
*
* PreCondition: none
*
* Input: None
*
* Output: true if successful, false otherwise
*
********************************************************************/
bool LCD_Initialize(void);

/*********************************************************************
* Function: void LCD_PutString(char* inputString, uint16_t length);
*
* Overview: Puts a string on the LCD screen.  Unsupported characters will be
*           discarded.  May block or throw away characters is LCD is not ready
*           or buffer space is not available.  Will terminate when either a
*           null terminator character (0x00) is reached or the length number
*           of characters is printed, which ever comes first.
*
* PreCondition: already initialized via LCD_Initialize()
*
* Input: char* - string to print
*        uint16_t - length of string to print
*
* Output: None
*
********************************************************************/
void LCD_PutString(char* inputString, uint16_t length);

/*********************************************************************
* Function: void LCD_PutChar(char);
*
* Overview: Puts a character on the LCD screen.  Unsupported characters will be
*           discarded.  May block or throw away characters is LCD is not ready
*           or buffer space is not available.
*
* PreCondition: already initialized via LCD_Initialize()
*
* Input: char - character to print
*
* Output: None
*
********************************************************************/
void LCD_PutChar(char);

/*********************************************************************
* Function: void LCD_ClearScreen(void);
*
* Overview: Clears the screen, if possible.
*
* PreCondition: already initialized via LCD_Initialize()
*
* Input: None
*
* Output: None
*
********************************************************************/
void LCD_ClearScreen(void);

/*********************************************************************
* Function: void LCD_CursorEnable(bool enable)
*
* Overview: Enables/disables the cursor
*
* PreCondition: None
*
* Input: bool - specifies if the cursor should be on or off
*
* Output: None
*
********************************************************************/
void LCD_CursorEnable(bool enable);

/**** End Microchip LCD H ****/

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

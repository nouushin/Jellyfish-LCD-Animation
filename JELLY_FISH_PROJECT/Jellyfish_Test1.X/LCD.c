/* 
 * File:        LCD.c
 * Description: Library of LCD routines for the for the dsPIC33CH128MP508 on 
 *               a Microchip Explorer 16/32
 * Author:      Michael Boldin
 *              <mboldin@niagaracollege.ca>
 *
 * Created on January 19, 2019, 2:32 PM
 * 
 ****************************************************************************
 *  Portions originally written by Professor Mark Csele 2006/09
 *  as LCD Test program for the 18F452 on a PICPROTO-II (up to 20MHz)
 ****************************************************************************
 *  Portions Copyright 2016 Microchip Technology Inc. (www.microchip.com)
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 * 
 ****************************************************************************
 *
 *  Modification History:
 *  --------------------
 *  2013.01.16  (MB) Created template from Buttons.asm (Pushbuttons_CtoF_PTB)
 *  2013.01.27  (MB) Changed oscillator setting from XT to HS; added tables
 *  2013.03.04  (MB) Copied from LCDTest18F.asm and modified;
 *                    converted to re-entrant code (save BSR, WREG, and STATUS)
 *  2019.01.19  (MB) Ported to C
 *  2019.01.19  (MB) Added putch()
 *  2020.02.11  (MB) Added LCD_ToLineCol(); corrected LCD_Line1()
 *
 *  2021-11-04   (MB)    Joined LCD_PTB.h with Microchip's
 *                        Explorer 16/32 demo code
 *  2021-11-05   (MB)    Started port and merge process;
 *                        moved hardware-specific constants here;
 *                        completed port and tested
 *  2021-11-05   (MB)    Fixed LCD_Home, LCD_Line1, LCD_Line2 to update
 *                        row and column globals to synchronize with
 *                        LCD_PutChar and other Microchip functions;
 *                        LCD_Char now calls LCD_PutChar
 * 2024-02-11    (MC)    Changed TRISE mask from 00FFh to 03FFh in function
 *                        LCD_Initialize to not overwrite button config.  
 *
 ***************************************************************************
 * 
 * MPLAB X Version: 	5.20
 * XC16 Version:        1.36
 * Editor:              default settings
 *
 *        1         2         3         4         5         6         7
123456789012345678901234567890123456789012345678901234567890123456789012345678
 *
 ****************************************************************************
 *  Hardware:
 *  --------
 *  dsPIC33CH128MP508 DSC
 *  CLK = 8 MHz (f_osc, f_cy = 4 MHz)
 *  RE15..RE12  - LCD Data Lines (to D7..D4)
 *  N/C         - LCD R/W Line (J19 is uncapped, pulled down to ground by R116)
 *  RE10        - LCD Enable Line
 *  RE11        - LCD RS (register select) Line
 * 
 ****************************************************************************
 *  Public Functions
 *  ================
 *  LCD_Init    Initialize the LCD I/O lines and display for normal, 
 *               8-bit operation. 
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

#include <xc.h>
#include <string.h>
#define FCY     4000000 /* 4 MHz, FOSC = 8 MHz */
#include <libpic30.h>

#include "LCD.h"

/*** Begin Microchip LCD.c ***/

/* Private Definitions ***********************************************/

#define LCD_FAST_INSTRUCTION_TIME_US    50
#define LCD_SLOW_INSTRUCTION_TIME_US    1600
#define LCD_STARTUP_TIME_MS             30
#define LCD_SIGNAL_TIMING_US            1

#define LCD_MAX_COLUMN                  16

#define LCD_COMMAND_CLEAR_SCREEN        0x01
#define LCD_COMMAND_RETURN_HOME         0x02
#define LCD_COMMAND_ENTER_DATA_MODE     0x06
#define LCD_COMMAND_CURSOR_OFF          0x0C
#define LCD_COMMAND_CURSOR_ON           0x0F
#define LCD_COMMAND_MOVE_CURSOR_LEFT    0x10
#define LCD_COMMAND_MOVE_CURSOR_RIGHT   0x14
#define LCD_COMMAND_SET_MODE_4_BIT      0x28
#define LCD_COMMAND_SET_MODE_8_BIT      0x38
#define LCD_COMMAND_ROW_0_HOME          0x80
#define LCD_COMMAND_ROW_1_HOME          0xC0
#define LCD_START_UP_COMMAND_1          0x33    
#define LCD_START_UP_COMMAND_2          0x32    

#define LCD_DATA_LAT                    LATE
#define LCD_DATA_TRIS                   TRISE

#define LCD_RSSignal_Set()    LATEbits.LATE11 = 1 //set Register Select bit
#define LCD_RSSignal_Clear()  LATEbits.LATE11 = 0 //clear Register Select bit
#define LCD_RSSignal_Input()  TRISEbits.TRISE11 = 1 //set Register Select bit
#define LCD_RSSignal_Output() TRISEbits.TRISE11 = 0 //clear Register Select bit

#define LCD_RWSignal_Set()        
#define LCD_RWSignal_Clear()      
#define LCD_RWSignal_Input()      
#define LCD_RWSignal_Output()     

#define LCD_EnableSignal_Set()    LATEbits.LATE10 = 1  //set Enable bit
#define LCD_EnableSignal_Clear()  LATEbits.LATE10 = 0  //clear Enable bit
#define LCD_EnableSignal_Input()  TRISEbits.TRISE10 = 1  //set Enable bit
#define LCD_EnableSignal_Output() TRISEbits.TRISE10 = 0  //clear Enable bit

/* Private Functions *************************************************/

static void LCD_CarriageReturn      ( void ) ;
static void LCD_ShiftCursorLeft     ( void ) ;
static void LCD_ShiftCursorRight    ( void ) ;
static void LCD_ShiftCursorUp       ( void ) ;
static void LCD_ShiftCursorDown     ( void ) ;
static void LCD_SendData            ( char ) ;
static void LCD_SendCommand         ( unsigned int ) ;

/* Private variables ************************************************/

static uint8_t row ;
static uint8_t column ;

/**** End Microchip LCD.c ****/


/***************************************************************************
 *  Initialize LCD
 ***************************************************************************
 *  Initialize the LCD I/O lines and display for normal, 8-bit operation. 
 ***************************************************************************/

void 
LCD_Init( void )
{
    (void) LCD_Initialize( ) ;  // always returns true anyway
}


/*****************************************************************************
 * LCD_Cmd, LCD_Char
 *****************************************************************************
 * Send a command or character to the LCD
 *****************************************************************************/

void 
LCD_Char( unsigned char ch )
{
    LCD_PutChar( (char) ch ) ;
}

void 
LCD_Cmd( unsigned char cmd )
{
    LCD_SendCommand( (unsigned int) cmd ) ;
}


/***************************************************************************
 *  LCD_Clear, LCD_Home
 ***************************************************************************
 *  Clear Screen or Move to Home (Line 1, Column 1)
 ***************************************************************************/

void 
LCD_Clear( void )
{
    LCD_ClearScreen( ) ;
}

void 
LCD_Home(void)
{
	LCD_SendCommand( LCD_COMMAND_RETURN_HOME ) ;	/* Home Display */
    
    row = column = 0 ;  // synchronize with LCD_PutChar
}


/***************************************************************************
 *  LCD_Line1, LCD_Line2
 ***************************************************************************
 *  Position cursor at start of line 1 or line 2 on the LCD display
 ***************************************************************************/

void 
LCD_Line1( void )
{
	LCD_SendCommand( LCD_COMMAND_ROW_0_HOME ) ;	/* Position cursor on line 1 */
    row = 0 ;       // synchronize with LCD_PutChar
    column = 0 ;
}

void 
LCD_Line2( void )
{
	LCD_SendCommand( LCD_COMMAND_ROW_1_HOME ) ;	/* Position cursor on line 2 */
    row = 1 ;       // synchronize with LCD_PutChar
    column = 0 ;
}

void 
LCD_ToLineCol( int line, int col )
{
    bool ok_b = false ;
    
    if ( ( line >= 1 ) && ( col >= 1 ) &&
         ( line <= LCD_LINES ) && ( col <= LCD_CHARS_PER_LINE ) )
    {
        if ( line == 1 )
        {
            LCD_SendCommand( LCD_COMMAND_ROW_0_HOME + col - 1 ) ;
            ok_b = true ;
        }
        else if ( line == 2 )
        {
            LCD_SendCommand( LCD_COMMAND_ROW_1_HOME + col - 1 ) ;
            ok_b = true ;
        }
    }
    
    if ( ok_b )    // synchronize with LCD_PutChar
    {
        row = line - 1 ;
        column = col - 1 ;
    }
    else
    {
        LCD_Clear( ) ;
        LCD_StringOut( "LCD_ToLineCol" ) ;
        LCD_Line2( ) ;
        LCD_StringOut( " error!" ) ;
    }
}


/***************************************************************************
 *  LCD_StringOut
 ***************************************************************************
 *  Output a preloaded, zero-terminated string to the LCD
 **************************************************************************/

void 
LCD_StringOut( const char * s )
{
    LCD_PutString( (char *) s, (uint16_t) strlen( s ) ) ;
}


/*** Begin Microchip LCD.c ***/

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
 * Output: true if initialized, false otherwise
 *
 ********************************************************************/
bool 
LCD_Initialize( void )
{
    //clear data bus
    LATE &= 0x03FF ;   // Using 0x00FF will affect button config, mask with 03FFh
    //drive to output
    TRISE &= 0x03FF ;  // Using 0x00FF will affect button config, mask with 03FFh

    // Control signal data pins
    LCD_RWSignal_Clear( ) ; // LCD R/W signal
    LCD_RSSignal_Clear( ) ; // LCD RS signal
    LCD_EnableSignal_Clear( ) ;     // LCD E signal

    // Control signal pin direction
    LCD_RSSignal_Output( )  ;
    LCD_RWSignal_Output( )  ;
    LCD_EnableSignal_Output( ) ;

    LCD_EnableSignal_Set( )  ;
    
    __delay_ms( LCD_STARTUP_TIME_MS ) ;
    
    LCD_SendCommand( LCD_COMMAND_SET_MODE_4_BIT  ) ;
    LCD_SendCommand( LCD_COMMAND_CURSOR_OFF  ) ;
    LCD_SendCommand( LCD_COMMAND_ENTER_DATA_MODE ) ;

    LCD_ClearScreen( ) ;

    return true ;
}


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
void 
LCD_PutString( char * inputString , uint16_t length )
{
    while ( length-- )
    {
        switch ( *inputString )
        {
            case 0x00:
                return ;

            default:
                LCD_PutChar( *inputString++ ) ;
                break ;
        }
    }
}


/*********************************************************************
 * Function: void LCD_PutChar(char);
 *
 * Overview: Puts a character on the LCD screen.  Unsupported characters will 
 *           be discarded.  May block or throw away characters is LCD is not 
 *           ready or buffer space is not available.
 *
 * PreCondition: already initialized via LCD_Initialize()
 *
 * Input: char - character to print
 *
 * Output: None
 *
 ********************************************************************/
void 
LCD_PutChar( char inputCharacter )
{
    static char lastCharacter = 0 ;
        
    switch ( inputCharacter )
    {
        case '\r':
            if ( lastCharacter != '\n' )
            {
                LCD_CarriageReturn( ) ;
            }
            break ;

        case '\n': 
            if( lastCharacter != '\r' )
            {
                LCD_CarriageReturn( ) ;
            }
            
            if ( row == 0 )
            {
                LCD_ShiftCursorDown( ) ;
            }
            else
            {
                LCD_ShiftCursorUp( ) ;
            }
            break ;

        case '\b':
            LCD_ShiftCursorLeft( ) ;
            LCD_PutChar( ' ' ) ;
            LCD_ShiftCursorLeft( ) ;
            break ;
            
        case '\f':
            LCD_ClearScreen( ) ;
            break;

        default:
            if ( column == LCD_MAX_COLUMN )
            {
                column = 0 ;
                if ( row == 0 )
                {
                    LCD_SendCommand( LCD_COMMAND_ROW_1_HOME ) ;
                    row = 1 ;
                }
                else
                {
                    LCD_SendCommand( LCD_COMMAND_ROW_0_HOME ) ;
                    row = 0 ;
                }
            }
            
            LCD_SendData( inputCharacter ) ;
            column++ ;
            break ;
    }
    
    lastCharacter = inputCharacter ;
}


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
void 
LCD_ClearScreen( void )
{
    LCD_SendCommand( LCD_COMMAND_CLEAR_SCREEN ) ;
    LCD_SendCommand( LCD_COMMAND_RETURN_HOME ) ;

    row = 0 ;
    column = 0 ;
}



/*******************************************************************/
/* Private Functions ***********************************************/
/*******************************************************************/


/*********************************************************************
 * Function: static void LCD_CarriageReturn(void)
 *
 * Overview: Handles a carriage return
 *
 * PreCondition: already initialized via LCD_Initialize()
 *
 * Input: None
 *
 * Output: None
 *
 ********************************************************************/
static void 
LCD_CarriageReturn( void )
{
    if ( row == 0 )
    {
        LCD_SendCommand( LCD_COMMAND_ROW_0_HOME ) ;
    }
    else
    {
        LCD_SendCommand( LCD_COMMAND_ROW_1_HOME ) ;
    }
    
    column = 0 ;
}


/*********************************************************************
 * Function: static void LCD_ShiftCursorLeft(void)
 *
 * Overview: Shifts cursor left one spot (wrapping if required)
 *
 * PreCondition: already initialized via LCD_Initialize()
 *
 * Input: None
 *
 * Output: None
 *
 ********************************************************************/
static void 
LCD_ShiftCursorLeft( void )
{
    uint8_t i ;

    if ( column == 0 )
    {
        if ( row == 0 )
        {
            LCD_SendCommand( LCD_COMMAND_ROW_1_HOME ) ;
            row = 1 ;
        }
        else
        {
            LCD_SendCommand( LCD_COMMAND_ROW_0_HOME ) ;
            row = 0 ;
        }

        // Now shift to the end of the row
        for ( i = 0 ; i < ( LCD_MAX_COLUMN - 1 ) ; i++ )
        {
            LCD_ShiftCursorRight( ) ;
        }
    }
    else
    {
        column-- ;
        LCD_SendCommand( LCD_COMMAND_MOVE_CURSOR_LEFT ) ;
    }
}


/*********************************************************************
 * Function: static void LCD_ShiftCursorRight(void)
 *
 * Overview: Shifts cursor right one spot (wrapping if required)
 *
 * PreCondition: already initialized via LCD_Initialize()
 *
 * Input: None
 *
 * Output: None
 *
 ********************************************************************/
static void 
LCD_ShiftCursorRight( void )
{
    LCD_SendCommand( LCD_COMMAND_MOVE_CURSOR_RIGHT ) ;
    column++ ;

    if ( column == LCD_MAX_COLUMN )
    {
        column = 0 ;
        if ( row == 0 )
        {
            LCD_SendCommand( LCD_COMMAND_ROW_1_HOME ) ;
            row = 1 ;
        }
        else
        {
            LCD_SendCommand( LCD_COMMAND_ROW_0_HOME ) ;
            row = 0 ;
        }
    }
}


/*********************************************************************
 * Function: static void LCD_ShiftCursorUp(void)
 *
 * Overview: Shifts cursor up one spot (wrapping if required)
 *
 * PreCondition: already initialized via LCD_Initialize()
 *
 * Input: None
 *
 * Output: None
 *
 ********************************************************************/
static void 
LCD_ShiftCursorUp( void )
{
    uint8_t i ;

    for ( i = 0 ; i < LCD_MAX_COLUMN ; i++ )
    {
        LCD_ShiftCursorLeft( ) ;
    }
}


/*********************************************************************
 * Function: static void LCD_ShiftCursorDown(void)
 *
 * Overview: Shifts cursor down one spot (wrapping if required)
 *
 * PreCondition: already initialized via LCD_Initialize()
 *
 * Input: None
 *
 * Output: None
 *
 ********************************************************************/
static void 
LCD_ShiftCursorDown( void )
{
    uint8_t i ;

    for ( i = 0 ; i < LCD_MAX_COLUMN ; i++ )
    {
        LCD_ShiftCursorRight( ) ;
    }
}


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
void 
LCD_CursorEnable( bool enable )
{
    if ( enable == true )
    {
        LCD_SendCommand( LCD_COMMAND_CURSOR_ON ) ;
    }
    else
    {
        LCD_SendCommand( LCD_COMMAND_CURSOR_OFF ) ;
    }
}


/*********************************************************************
 * Function: static void LCD_SendData(char data)
 *
 * Overview: Sends data to LCD
 *
 * PreCondition: None
 *
 * Input: char - contains the data to be sent to the LCD
 *
 * Output: None
 *
 ********************************************************************/
static void 
LCD_SendData( char data )
{
    // Split data into nibbles 
    int data_shift = data << 8 ;
    int upper_nibble = data_shift & 0xF000 ;
    int lower_nibble = data_shift & 0x0F00 ;
    lower_nibble = lower_nibble << 4 ;
    
    LCD_RWSignal_Clear( ) ;
    LCD_RSSignal_Set( ) ;
    LATE &= 0x0FFF ;
    LATE |= upper_nibble ;
    __delay_us(LCD_SIGNAL_TIMING_US) ;
    LCD_EnableSignal_Set( ) ;
    __delay_us(LCD_SIGNAL_TIMING_US) ;
    
    LCD_EnableSignal_Clear( ) ;
    LATE &= 0x0FFF ;
    LATE |= lower_nibble ;
    __delay_us(LCD_SIGNAL_TIMING_US);
    LCD_EnableSignal_Set( ) ;
    __delay_us(LCD_SIGNAL_TIMING_US);
    LCD_EnableSignal_Clear( ) ;
    LCD_RSSignal_Clear( ) ;
    __delay_us(LCD_FAST_INSTRUCTION_TIME_US);
}


/*********************************************************************
 * Function: static void LCD_SendCommand(char data)
 *
 * Overview: Sends command to LCD
 *
 * PreCondition: None
 *
 * Input: char - contains the command to be sent to the LCD
 *        unsigned int - has the specific delay for the command
 *
 * Output: None
 *
 ********************************************************************/
static void 
LCD_SendCommand( unsigned int command )
{
    int cmd_shift = command << 8 ;
    int upper_nibble = cmd_shift & 0xF000 ;
    int lower_nibble = cmd_shift & 0x0F00 ;
    lower_nibble = lower_nibble << 4 ;
    
    LCD_RWSignal_Clear( ) ;
    LCD_RSSignal_Clear( ) ;
    LATE &= 0x0FFF ;
    LATE |= upper_nibble ;
    
    LCD_EnableSignal_Set( ) ;
    __delay_us(LCD_SIGNAL_TIMING_US);
    LCD_EnableSignal_Clear( ) ;
    
    LCD_RWSignal_Clear( ) ;
    LCD_RSSignal_Clear( ) ;
    LATE &= 0x0FFF ;
    LATE |= lower_nibble ;
   
    LCD_EnableSignal_Set( ) ;
    __delay_us(LCD_SIGNAL_TIMING_US);
    LCD_EnableSignal_Clear( ) ;  
    
    switch( command )
    {
        case LCD_COMMAND_MOVE_CURSOR_LEFT:
        case LCD_COMMAND_MOVE_CURSOR_RIGHT:
        case LCD_COMMAND_SET_MODE_8_BIT:
		case LCD_COMMAND_SET_MODE_4_BIT:
        case LCD_COMMAND_CURSOR_OFF:
            __delay_us(LCD_FAST_INSTRUCTION_TIME_US);
            break ;
            
        case LCD_COMMAND_ENTER_DATA_MODE:
        case LCD_COMMAND_CLEAR_SCREEN:
        case LCD_COMMAND_RETURN_HOME:
        case LCD_COMMAND_CURSOR_ON:
        case LCD_COMMAND_ROW_0_HOME:
        case LCD_COMMAND_ROW_1_HOME:
        default:
            __delay_us(LCD_SLOW_INSTRUCTION_TIME_US);
            break ;
    }
}

/**** End Microchip LCD.c ****/

///*** Begin Microchip LCD_printf.c ***/
//
//int __attribute__((__section__(".libc.write"))) 
//write( int handle, void *buffer, unsigned int len ) 
//{
//    LCD_PutString( buffer, len ) ;
//    return ( len ) ;
//}
//
///**** End Microchip LCD_printf.c ****/

/*** END LCD.c */

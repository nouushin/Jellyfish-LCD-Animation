
/*** DO NOT MODIFY CODE IN THIS FILE ***/

/*******************************************************************************
 *  Function:     dbgInit()
 *  Description:  Initializes debugging features
 *  Parameters:   None
 *  Returns:      Nothing
 *  Notes:        This function is for DEBUGGING ONLY
 ******************************************************************************/
void dbgInit()
{
    // Initialize UART1 for use as a debugging console output
    UART1_Init();
    
    // Configure port pin E9 on Explorer 16/32 board as an input for SW4
    TRISEbits.TRISE9 = 1;  
    
    // Map EXT INT1 to desired pin re-mappable pin
    PPS_ExtInt1();
}

/*******************************************************************************
 *  Function:     dbgPause()
 *  Description:  Pauses code execution until SW4 pressed.
 *  Parameters:   None
 *  Returns:      Nothing
 *  Notes:        This function is for DEBUGGING ONLY
 ******************************************************************************/
void dbgPause()
{	
    int wait=1;
    
    // Disable all configured interrupts (Global interrupt flag)
    INTCON2bits.GIE = 0; 
    
	// Display "pause" message
    dbgPrintf("\r\n-------------pause-------------");
	
    // Wait for SW3 press on Explorer 16/32 board to resume
    while (wait)
    {
        wait = PORTEbits.RE9;
    }
    __delay_ms(dbgSW_DEBOUNCE_MS);
    
    // Re-enable all configured interrupts (Global interrupt flag)
    INTCON2bits.GIE = 1; 
}

/*******************************************************************************
 *  Function:     PPS_ExtInt1()
 *  Description:  Configures external interrupt 1 for device pin 1 via PPS
 *  Parameters:   None
 *  Returns:      Nothing
 *  Notes:        N/A
 ******************************************************************************/
void PPS_ExtInt1()
{
    // Unlock Peripheral Pin Select (PPS) configuration
    RPCONbits.IOLOCK = 0;

    // Set Port B bit 16, device pin 1, re-mappable pin 46 to INT1
    _INT1R = 46;

    // Lock PPS configuration         
    RPCONbits.IOLOCK = 1;
}

/*******************************************************************************
 *  Function:     PPS_UART1()
 *  Description:  Configures UART1 RX/TX for device pins 66/67 via PPS
 *  Parameters:   None
 *  Returns:      Nothing
 *  Notes:        N/A
 ******************************************************************************/
void PPS_UART1()
{
    // Unlock Peripheral Pin Select (PPS) configuration
    RPCONbits.IOLOCK = 0;

    // Pin 67 (C11) as output pin for UART1 TX
    TRISCbits.TRISC11 = 0;                               
    _RP59R = 1;   
    
    // Pin 66 (C10) as input pin for UART1 RX 
    TRISCbits.TRISC10 = 1; 
    _U1RXR = 58;

    // Lock PPS configuration         
    RPCONbits.IOLOCK = 1;
}

/*******************************************************************************
 *  Function:     UART1_Init()
 *  Description:  Configures UART1 for operation as a debugging/console output
 *  Parameters:   None
 *  Returns:      Nothing
 *  Notes:        RX disabled, 
 *                8 data bits, 
 *                No parity bit, 
 *                1 stop bit, 
 *                No flow control
 ******************************************************************************/
void UART1_Init()
{
    // Use the Peripheral Pin Select (PPS) to configure UART1 to use the pins
    // connected to the USB-to-Serial bridge on the Explorer 16/32 board.
    PPS_UART1();
    
    // See dsPIC33CH128MP508 datasheet Section 13.5, for full register details
    
    /* U1MODE (CONFIGURATION REGISTER) */
    U1MODEbits.MOD = 0;         // 8 bit data, no parity bit   
    U1MODEbits.URXEN = 0;       // Disable UART RX (only using for debug output)    
    U1MODEbits.UTXEN = 1;       // Enable UART TX
    U1MODEbits.ABAUD = 0;       // Disable Auto-Baud Detect
    U1MODEbits.BRGH = 0;        // Disable high speed baud rate
    U1MODEbits.UTXBRK = 0;      // Disable UART Transmit Break bit
    U1MODEbits.BRKOVR = 0;      // Disable Send Break Software Override bit
    U1MODEbits.RXBIMD = 0;      // Receive Break Interrupt Mode bit
    U1MODEbits.WAKE = 0;        // Disable wakeup option
    U1MODEbits.USIDL = 0;       // Continue working when Idle      ???
    U1MODEbits.UARTEN = 1;      // Enable UART
    
    /* U1MODEH (CONFIGURATION REGISTER HIGH) */
    U1MODEHbits.FLO = 0;        // Flow control off
    U1MODEHbits.UTXINV = 0;     // Output data are not inverted
    U1MODEHbits.C0EN = 0;       // Checksum Mode 0 (Lin mode only)
    U1MODEHbits.STSEL = 0;      // 1 Stop bit
    U1MODEHbits.URXINV = 0;     // Input is not inverted; Idle state is high
    U1MODEHbits.RUNOVF = 0;     // Run During Overflow Condition Mode bit
    U1MODEHbits.HALFDPLX = 0;   // UART Half-Duplex Selection Mode bit
    U1MODEHbits.BCLKSEL = 0;    // Baud Clock Source Selection bits
    U1MODEHbits.BCLKMOD = 0;    // Baud Clock Generation Mode Select bit
    U1MODEHbits.ACTIVE = 0;     // UART Running Status bit
    U1MODEHbits.SLPEN = 0;      // Run During Sleep Enable bit
    
    /* U1STA (STATUS REGISTER) */
    U1STAbits.OERR = 0;         // Receive Buffer Overflow Interrupt Flag bit
    
    /* U1STAH (STATUS REGISTER HIGH) */
    U1STAHbits.UTXISEL = 0;     // UART Transmit Interrupt Select bits
    U1STAHbits.URXISEL = 0;     // UART Receive Interrupt Select bits
    
    // Baud Rate setting for 19200
    U1BRG = dbgBRGVAL;    
    
    // Clear the transmit and receive interrupt flags 
    IFS0bits.U1TXIF = 0;
    IFS0bits.U1RXIF = 0;
    
    // Enable UART TX interrupt
    IEC0bits.U1TXIE = 1;
    // Disable UART RX interrupt (only using for debug output)
    IEC0bits.U1RXIE = 0;   
    
    // Redirect printf statements to use UART1
    __C30_UART = 1; 
    
    // Load transmit register with null (i.e. clear it)
    U1TXREG = 0;
    
    // Send return & newLine
    dbgPrintf("\r\n");
}

/*******************************************************************************
* 				  UART1 INTERRUPTS SERVICE ROUTINE FUNCTIONS                   *
*******************************************************************************/
void __attribute__((__interrupt__, __auto_psv__)) _U1TXInterrupt(void)
{    
    IFS0bits.U1TXIF = 0;    // Clear TX Interrupt flag
}
void __attribute__((__interrupt__, __auto_psv__)) _U1RXInterrupt(void)
{
    // UART1 RX functionality and interrupt currently not enabled
    IFS0bits.U1RXIF = 0;    // Clear RX Interrupt flag
}
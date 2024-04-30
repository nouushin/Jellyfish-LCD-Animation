/*
 * File:   main.c
 * Author: dsantana
 *
 * Created on March 20, 2024, 10:27 AM
 * Last modified on April 30, 2024, 3:00 PM
 * - Added more comments to explain missing parts of the code related to the buttons
 * - Changed code under buttons to include more settings from the board.
 *           ~unsuccesfully the buttons are not being read~
 */

#include "main.h"
#include "LCD.h"
#include "LCD.c"

//variables for button de-bounce
bool btnDebounce = FALSE;
uint16_t msBtnDebounce = 0;
#define BTN_DEBOUNCE_MS 250

//variables for sequence
int currentSequence = 0; //keep track of current sequence index
#define NUM_SEQUENCES 4  //total number of sequences

//animation control
uint16_t BASE_DELAY_MS = 1000; //(1sec)
bool animationRunning = TRUE;
char i = 0;

////////////////////////////////////////////////////////
/////////// PIXEL ANIMATION CONSTANTS/POSITION /////////
////////////////////////////////////////////////////////

//First sequence//
uint16_t Jelly_1[8] = {
  0x6, 0x1, 0x0, 0x3, 0x4, 0x1, 0x6, 0x0 //hex 
};
uint16_t Jelly_2[8] = {
  0x18, 0x4, 0x4, 0x4, 0x18, 0x0, 0x0, 0x0
};
uint16_t Jelly_3[8] = {
  0x8, 0x14, 0x8, 0x0, 0x0, 0x0, 0x0, 0x0
};
uint16_t Jelly_4[8] = {
  0x0, 0x0, 0x0, 0x0, 0x8, 0x14, 0x8, 0x0
};

//Second sequence//
uint16_t Jelly_5[8] = {
  0x0, 0x0, 0x18, 0x4, 0x4, 0x4, 0x18, 0x0
};
uint16_t Jelly_6[8] = {
  0x0, 0x0, 0x6, 0x1, 0x4, 0x2, 0x1, 0x6
};
uint16_t Jelly_7[8] = {
  0x0, 0x0, 0x0, 0x0, 0x0, 0x8, 0x14, 0x8
};
uint16_t Jelly_8[8] = {
  0x0, 0x0, 0x0, 0x0, 0x0, 0x4, 0x2a, 0x4
};

//Third sequence//
uint16_t Jelly_9[8] = {
  0x0, 0x0, 0x18, 0x4, 0x4, 0x4, 0x18, 0x0
};
uint16_t Jelly_10[8] = {
  0x4, 0x2, 0x1, 0x4, 0x3, 0x1, 0x2, 0x4
};
uint16_t Jelly_11[8] = {
  0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x5, 0x2
};
uint16_t Jelly_12[8] = {
  0x0, 0x0, 0x8, 0x14, 0x8, 0x0, 0x0, 0x0
};

//Forth sequence//
uint16_t Jelly_13[8] = {
  0x2, 0x2, 0x1, 0x4, 0x3, 0x1, 0x6, 0x0
};
uint16_t Jelly_14[8] = {
  0x0, 0x0, 0x2a, 0x15, 0x11, 0x2a, 0x4, 0x0
};
uint16_t Jelly_15[8] = {
  0x0, 0x18, 0x4, 0x4, 0x4, 0x18, 0x0, 0x0
};

////////////////////////////////////////////////////////
/////////// FUNCTIONS TO SHOW CUSTOM CHARACTER /////////
////////////////////////////////////////////////////////

void InitCustomChar1(){
    //FIRST SEQUENCE
    //char i; (can also be set as a local variable in the functions)
    
    LCD_Cmd(0x40); //sets CGRAM Address 
    for (i = 0; i < 8; i++){
        LCD_Char(Jelly_1[i]); //first 5x8 position
    }
    LCD_Cmd(0x48); //sets CGRAM Address
    for (i = 0; i < 8; i++){    
        LCD_Char(Jelly_2[i]);
    }
    LCD_Cmd(0x50); //sets CGRAM Address 
    for (i = 0; i < 8; i++){    
        LCD_Char(Jelly_3[i]);
    }
    LCD_Cmd(0x58); //sets CGRAM Address
    for (i = 0; i < 8; i++){    
        LCD_Char(Jelly_4[i]);
    }
    
    //move or update LCD screen in corresponding col/line
    LCD_ToLineCol(2,1); //moves to designated position
    LCD_Char(0);        //calls for the designated custom characters according to order of creation
        
    LCD_ToLineCol(2,2); //moves to designated position
    LCD_Char(1);
        
    LCD_ToLineCol(2,3); //moves to designated position
    LCD_Char(2);
        
    LCD_ToLineCol(1,1); //moves to designated position
    LCD_Char(3);           
}

void InitCustomChar2(){
    //SECOND SEQUENCE
    //char i;
    LCD_Clear();
    
    LCD_Cmd(0x60); //sets CGRAM Address 
    for (i = 0; i < 8; i++){
        LCD_Char(Jelly_5[i]); //first 5x8 position
    }
    LCD_Cmd(0x68); //sets CGRAM Address
    for (i = 0; i < 8; i++){    
        LCD_Char(Jelly_6[i]);
    }
    LCD_Cmd(0x70); //sets CGRAM Address 
    for (i = 0; i < 8; i++){    
        LCD_Char(Jelly_7[i]);
    }
    LCD_Cmd(0x48); //sets CGRAM Address
    for (i = 0; i < 8; i++){    
        LCD_Char(Jelly_8[i]);
    }
    
    //move or update LCD screen in corresponding col/line
    LCD_ToLineCol(2,3); //moves to designated position
    LCD_Char(4);
        
    LCD_ToLineCol(2,2); //moves to designated position
    LCD_Char(5);
        
    LCD_ToLineCol(2,4); //moves to designated position
    LCD_Char(6);
        
    LCD_ToLineCol(1,3); //moves to designated position
    LCD_Char(7);          
}

void InitCustomChar3(){
    //THIRD SEQUENCE
    //char i;
    LCD_Clear();
    
    LCD_Cmd(0x50); //sets CGRAM Address 
    for (i = 0; i < 8; i++){
        LCD_Char(Jelly_9[i]); //first 5x8 position
    }
    LCD_Cmd(0x58); //sets CGRAM Address
    for (i = 0; i < 8; i++){    
        LCD_Char(Jelly_10[i]);
    }
    LCD_Cmd(0x60); //sets CGRAM Address 
    for (i = 0; i < 8; i++){    
        LCD_Char(Jelly_11[i]);
    }
    LCD_Cmd(0x68); //sets CGRAM Address
    for (i = 0; i < 8; i++){    
        LCD_Char(Jelly_12[i]);
    }
    
    //move or update LCD screen in corresponding col/line
    LCD_ToLineCol(2,4); //moves to designated position
    LCD_Char(8);
        
    LCD_ToLineCol(2,3); //moves to designated position
    LCD_Char(9);
        
    LCD_ToLineCol(1,4); //moves to designated position
    LCD_Char(10);
        
    LCD_ToLineCol(2,5); //moves to designated position
    LCD_Char(11); 
}

void InitCustomChar4(){
    //FORTH SEQUENCE
    //char i;
    LCD_Clear(); //clears display
    
    LCD_Cmd(0x70); //sets CGRAM Address 
    for (i = 0; i < 8; i++){
        LCD_Char(Jelly_13[i]); //first 5x8 position
    }
    LCD_Cmd(0xA0); //sets CGRAM Address
    for (i = 0; i < 8; i++){    
        LCD_Char(Jelly_14[i]);
    }
    LCD_Cmd(0xB0); //sets CGRAM Address 
    for (i = 0; i < 8; i++){    
        LCD_Char(Jelly_15[i]);
    }
        
    //move or update LCD screen in corresponding col/line
    LCD_ToLineCol(2,4); //moves to designated position
    LCD_Char(12);
        
    LCD_ToLineCol(2,6); //moves to designated position
    LCD_Char(13);
    
    LCD_ToLineCol(2,5); //moves to designated position
    LCD_Char(14);
}

////////////////////////////////////////////
/////////////  MAIN FUNCTION  //////////////
////////////////////////////////////////////

void main(){
    Init(); //initializes primary functions
    
    while(TRUE){
        Button_Check();
        
        if (animationRunning){
            //continue animation loop only if animation is running
            Start_LCD();
        }
    }
}

void Init(){
    
    dbgInit();
    Start_LCD();
    Start_Buttons();
} 

////////////////////////////////////////////////
///////// LCD INITIALIZATION FUNCTIONS /////////
////////////////////////////////////////////////

void Start_LCD(){
    LCD_Init();  //turn on display
    LCD_Clear(); //clears display
        
    //displays current sequence one by one
    switch(currentSequence) {
        case 0:
            InitCustomChar1();
            break;
        case 1:
            InitCustomChar2();
            break;
        case 2:
            InitCustomChar3();
            break;
        case 3:
            InitCustomChar4();
            break;   
        //if you create more sequences just add more cases and call them in the order you want     
    }

    __delay_ms(BASE_DELAY_MS);
    currentSequence++;
        
    if (currentSequence >= NUM_SEQUENCES){
        currentSequence = 0; //resets count od sequences to zero to continue the loop
    }
}    

////////////////////////////////////
////////// TIMER FUNCTIONS /////////
////////////////////////////////////

void __attribute__((__interrupt__)) _T1Interrupt(){
    
    IFS0bits.T1IF = 0; //clears interrupt flag
    
    if(btnDebounce){
        //helps with the button debounce in the board since there is no internal component for it
        //recommended to not modify the "if" statement
        msBtnDebounce++;
        
        if(msBtnDebounce == BTN_DEBOUNCE_MS){
            msBtnDebounce = 0;
            btnDebounce = FALSE;
        }
    }
    else{
        msBtnDebounce = 0;
    }
}

///////////////////////////////////////
///////// BUTTON FUNCTIONS ///////////
/////////////////////////////////////

void Start_Buttons(){
    
    //sets buttons to active low/high according to your necessities 
    TRISE = 0b01111111100000000;
    
    TRISBbits.TRISB14 = 1;  //SET TRIS bit for SW3
    TRISEbits.TRISE8 = 1;  //SET TRIS bit for SW6
    TRISEbits.TRISE7 = 1;  //SET TRIS bit for SW5
    TRISEbits.TRISE9 = 1;  //SET TRIS bit for SW4
    
    PPS_ExtInt1();
    
    CNPUEbits.CNPUE7 = 1;
    
    IEC0bits.INT1IE = 1;
    
    INTCON2bits.GIE = 1;
}

void Button_Check(){ 
    //checks that the button has been pressed and calls for specific function
    if(!btnDebounce){
        
        if(!PORTBbits.RB7){
            btnDebounce = TRUE; //set debounce flag
            StopAnimation(); //call function to stop animation
        }
        if(!PORTBbits.RB8){
            btnDebounce = TRUE;
            IncreaseSpeed(); //call function to increase speed in animation
        }
        if(!PORTBbits.RB14){
            btnDebounce = TRUE;
            DecreaseSpeed(); //call function to decrease spped in animation
        }
        if(!PORTBbits.RB9){
            btnDebounce = TRUE;
            ResumeAnimation(); //call function to continue animation after stopping it
        }
    }
}

///////////////////////////////////////////
/////////// BUTTON ACTIONS ////////////////
///////////////////////////////////////////

void StopAnimation(){
    //stop animation by pausing updates in the LCD
    //freeze the display in its current state
    animationRunning = FALSE;
}
void ResumeAnimation(){
    //resume the animation by re-starting updates to the LCD
    //restart Timer or any other timers/interrupts used for animation 
    animationRunning = TRUE;
}
void IncreaseSpeed(){
    //increase the animation speed by reducing the delay between frame updates
    BASE_DELAY_MS -= 100; //reduces 100ms
}
void DecreaseSpeed(){
    //decreases the animation speed by increasing the delay between frame updates
    if (BASE_DELAY_MS < 2000){
        BASE_DELAY_MS += 100; //reduces 100ms
    }
}


//===== End fo the code main.c ======

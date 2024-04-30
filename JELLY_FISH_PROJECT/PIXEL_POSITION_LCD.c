//                                                                 // 
// Author:         Debbie Santana                                  // 
// Date:           2024-04-08                                      //
// Modifications:  Last modified on 2024-04-30                     //
//                 Created comments to understand how it works     //
//-----------------------------------------------------------------//

//===== Table that shows the correlation between Hexadecimal, decimal and LCD bit display ======

HEX       LCD             DECIMAL
0x0  =    empty;             0      //The animation in C code is made in hexadecimal so use them according to what 
                                    //you want to show in the display.
0x1  = [ 0 0 0 0 1];         1
0x2  = [ 0 0 0 1 0];         2
0x4  = [ 0 0 1 0 0];         4
0x8  = [ 0 1 0 0 0];         8
0x10 = [ 1 0 0 0 0];        16

0x3  = [ 0 0 0 1 1];         3
0x6  = [ 0 0 1 1 0];         6
0xc  = [ 0 1 1 0 0];        12
0x18 = [ 1 1 0 0 0];        24

0x7  = [ 0 0 1 1 1];         7
0xe  = [ 0 1 1 1 0];        14
0x1c = [ 1 1 1 0 0];        28

0x5  = [ 0 0 1 0 1];        65
0xf  = [ 0 1 1 1 1];        15
0x1e = [ 1 1 1 1 0];        30
0x1f = [ 1 1 1 1 1];        31

0x9  = [ 0 1 0 0 1];         9
0x11 = [ 1 0 0 0 1];        17
0x12 = [ 1 0 0 1 0];        18
0x2a = [ 0 1 0 1 0];        42
0x15 = [ 1 0 1 0 1];        21
0x1a = [ 1 1 0 1 0];        26
0x19 = [ 1 1 0 0 1];        25
0x14 = [ 1 0 1 0 0];        20
0x16 = [ 1 0 1 1 0];        22

// The zeros (0) represent an empty bit and the one (1) is a black bit, meaning it is showing in the display

//Notes: The table is not complete for some combinations but if you need more you can guide yourself with the table
//and transform the binary to hex in an online converter or by yourself (not that hard).


//==== End of the code PIXEL_POSITION_LCD.c =====
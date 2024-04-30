/*                                                                // 
/ Author:         Debbie Santana                                  // 
/ Date:           2024-04-01                                      //
/ Modifications:  Last modified on 2024-04-30                     //
/                 Added more comments                             //
/-----------------------------------------------------------------//

===== this code was generated in c++ under the LyquidCrystal library =====

//First sequence of Jellyfish animation in LCD//
void image() {
lcd.clear();

byte image20[8] = {B01001, B10110, B00000, B00000, B00000, B00000, B00000, B00000};
byte image03[8] = {B01000, B10100, B01000, B00001, B00010, B00010, B00001, B00010};
byte image04[8] = {B00000, B00000, B00000, B01100, B00010, B00001, B00001, B00000};
byte image19[8] = {B01000, B00010, B00100, B00101, B11001, B00010, B00010, B00001};
byte image18[8] = {B00011, B00100, B00000, B00000, B00000, B01000, B10100, B01000};
byte image21[8] = {B00000, B00000, B00000, B00000, B01000, B10100, B01000, B00000};
byte image06[8] = {B00000, B00000, B00000, B00000, B00000, B01000, B10100, B01000};

lcd.createChar(0, image20);
lcd.createChar(1, image03);
lcd.createChar(2, image04);
lcd.createChar(3, image19);
lcd.createChar(4, image18);
lcd.createChar(5, image21);
lcd.createChar(6, image06);


lcd.setCursor(3, 1);
lcd.write(byte(0));
lcd.setCursor(2, 0);
lcd.write(byte(1));
lcd.setCursor(3, 0);
lcd.write(byte(2));
lcd.setCursor(2, 1);
lcd.write(byte(3));
lcd.setCursor(1, 1);
lcd.write(byte(4));
lcd.setCursor(4, 1);
lcd.write(byte(5));
lcd.setCursor(5, 0);
lcd.write(byte(6));

}

//second sequence//
void image() {
lcd.clear();

byte image06[8] = {B00000, B00000, B00000, B11000, B00100, B00010, B00010, B00010};
byte image05[8] = {B00000, B00000, B00000, B00011, B00100, B00100, B00010, B11100};
byte image22[8] = {B10010, B01100, B00000, B00000, B00000, B00000, B00000, B00000};
byte image21[8] = {B11000, B00001, B11010, B00000, B00000, B00000, B00000, B00000};
byte image04[8] = {B00000, B00010, B00010, B00100, B00010, B10001, B10001, B01000};
byte image20[8] = {B00011, B00000, B00011, B01100, B10000, B00000, B00000, B00000};


lcd.createChar(0, image06);
lcd.createChar(1, image05);
lcd.createChar(2, image22);
lcd.createChar(3, image21);
lcd.createChar(4, image04);
lcd.createChar(5, image20);


lcd.setCursor(5, 0);
lcd.write(byte(0));
lcd.setCursor(4, 0);
lcd.write(byte(1));
lcd.setCursor(5, 1);
lcd.write(byte(2));
lcd.setCursor(4, 1);
lcd.write(byte(3));
lcd.setCursor(3, 0);
lcd.write(byte(4));
lcd.setCursor(3, 1);
lcd.write(byte(5));

}

//third sequence//
void image() {
lcd.clear();

byte image24[8] = {B00000, B00001, B00001, B00010, B01100, B00000, B00000, B00000};
byte image23[8] = {B11010, B00001, B00010, B00010, B00001, B00000, B00000, B00000};
byte image08[8] = {B00000, B00010, B00101, B00010, B00000, B00000, B10110, B01001};
byte image07[8] = {B01000, B00100, B00010, B00010, B10001, B10001, B01100, B00010};
byte image06[8] = {B00000, B00000, B00010, B00001, B00000, B00000, B00000, B00000};
byte image22[8] = {B01001, B00110, B00000, B00000, B00000, B00010, B00101, B00010};
byte image25[8] = {B00000, B00000, B00000, B00000, B00010, B00101, B00010, B00000};


lcd.createChar(0, image24);
lcd.createChar(1, image23);
lcd.createChar(2, image08);
lcd.createChar(3, image07);
lcd.createChar(4, image06);
lcd.createChar(5, image22);
lcd.createChar(6, image25);


lcd.setCursor(7, 1);
lcd.write(byte(0));
lcd.setCursor(6, 1);
lcd.write(byte(1));
lcd.setCursor(7, 0);
lcd.write(byte(2));
lcd.setCursor(6, 0);
lcd.write(byte(3));
lcd.setCursor(5, 0);
lcd.write(byte(4));
lcd.setCursor(5, 1);
lcd.write(byte(5));
lcd.setCursor(8, 1);
lcd.write(byte(6));

}

//forth sequence//
void image() {
lcd.clear();

byte image24[8] = {B11010, B00001, B00010, B00010, B00001, B00000, B00000, B00000};
byte image07[8] = {B00000, B00000, B00000, B00110, B01001, B10010, B00010, B00001};
byte image09[8] = {B00000, B01100, B10010, B00000, B00000, B00000, B10110, B01001};
byte image25[8] = {B00000, B00001, B00001, B00010, B01100, B00000, B00000, B00000};
byte image08[8] = {B10000, B10000, B01001, B01001, B01000, B00101, B00100, B00010};
byte image10[8] = {B00000, B00000, B00000, B00010, B00101, B00010, B00000, B00000};
byte image26[8] = {B00000, B00000, B00000, B00000, B00000, B01000, B10100, B01000};
byte image23[8] = {B01000, B10100, B01000, B00000, B00000, B00000, B00000, B00000};


lcd.createChar(0, image24);
lcd.createChar(1, image07);
lcd.createChar(2, image09);
lcd.createChar(3, image25);
lcd.createChar(4, image08);
lcd.createChar(5, image10);
lcd.createChar(6, image26);
lcd.createChar(7, image23);


lcd.setCursor(7, 1);
lcd.write(byte(0));
lcd.setCursor(6, 0);
lcd.write(byte(1));
lcd.setCursor(8, 0);
lcd.write(byte(2));
lcd.setCursor(8, 1);
lcd.write(byte(3));
lcd.setCursor(7, 0);
lcd.write(byte(4));
lcd.setCursor(9, 0);
lcd.write(byte(5));
lcd.setCursor(9, 1);
lcd.write(byte(6));
lcd.setCursor(6, 1);
lcd.write(byte(7));

}

==== End of the code/comment of original Jellyfish sequence in c++ =====
*/
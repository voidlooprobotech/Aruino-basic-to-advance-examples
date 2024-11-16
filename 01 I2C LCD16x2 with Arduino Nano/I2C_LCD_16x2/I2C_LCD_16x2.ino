#include <Wire.h>     // include I2C library
#include<LiquidCrystal_I2C.h> // i2c LCD library
LiquidCrystal_I2C lcd(0x27,16,2);  // lcd class, 0x27 is i2c slave address, Lcd char is 16 and 2 line


void setup() {

  lcd.begin();  // LCD initialization
  lcd.backlight(); // lcd back light ON
  //lcd.setCursor(0,0);    // 5 means 6th number of char and 1st line
  lcd.print("Void loop");  // lcd printing command

}

void loop() {
  

}

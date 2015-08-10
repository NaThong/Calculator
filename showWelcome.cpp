#include "Header.h"
LiquidCrystal lcd5(8,9,10,11,12,13);
/*****************************************************************************
 * DISPLAY PURPOSES ONLY
 *****************************************************************************/
void showWelcome() 
{
  lcd5.begin(16, 2);
  lcd5.clear();
  lcd5.setCursor(0, 0);
  lcd5.print(" -=> Yoooo! <=-");
  for (byte i = 0; i < 16; i++) 
  {
    delay(100);
    lcd5.setCursor(i, 1);
    lcd5.write(byte(255));
  }
  delay(500);
  lcd5.clear();
}

#include "Header.h"

BinaryKeypad::BinaryKeypad()
{
  buttonArray[0] = 0;
  buttonArray[1] = 0;
  buttonArray[2] = 0;
  buttonArray[3] = 0;
  buttonArray[4] = 0;
  value          = 0;
  specialChar    = false;
}

BinaryKeypad::~BinaryKeypad(){}

void BinaryKeypad::SetKeyValue()
{
  value = 0;
  PauseUntilButtonPressed();
  
  buttonArray[0] = digitalRead(2); // 1
  buttonArray[1] = digitalRead(3); // 2
  buttonArray[2] = digitalRead(4); // 4
  buttonArray[3] = digitalRead(5); // 8
  buttonArray[4] = digitalRead(6); // 16
  
  value += buttonArray[0];      // 1
  value += buttonArray[1] * 2;  // 2
  value += buttonArray[2] * 4;  // 4
  value += buttonArray[3] * 8;  // 8
  value += buttonArray[4] * 16; // 16
  
  if(GetKeyValue() == 10)
  {
    value = 0;
  }
  
  if(buttonArray[4])
  {
    ToggleSpecialChar();
  }
}

void BinaryKeypad::PauseUntilButtonPressed()
{
  int j = 2;
  
  while(digitalRead(j) == 0)
  {
    j++;
    if(j == 7)
    {
      j = 2;
    }
  }
}

void BinaryKeypad::PauseUntilButtonReleased()
{
  boolean released = false;
  
  while(!released)
  {
    if(digitalRead(2) == 0 &&
       digitalRead(3) == 0 &&
       digitalRead(4) == 0 &&
       digitalRead(5) == 0 &&
       digitalRead(6) == 0)
    {
      released = true;
    }
  }
}

void BinaryKeypad::ToggleSpecialChar()
{
  specialChar = !specialChar;
}

const int BinaryKeypad::GetKeyValue()
{
  return value;
}

const boolean BinaryKeypad::GetSpecialChar()
{
  return specialChar;
}

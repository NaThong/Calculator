#include "Header.h"
LiquidCrystal lcd2(8,9,10,11,12,13);

Number::Number()
{
  Calculator::SetType('N');
  number     = 0;
  decimal    = false;
  count      = 0;
  deciCount  = 1;
}

Number::~Number(){}

void Number::SetNumber(float auxNumber)
{
  number = auxNumber;
}

void Number::CalculateNumber(int auxNumber)
{
  // If GetDecimal() is true then calculate decimal
  if(GetDecimal())
  {
      number = GetNumber() + float(auxNumber * pow(.1, deciCount));
       
      if(deciCount == 1)
      {
        count++;
      }
      
      deciCount++;
  }
  else
  {
    // If it's the first input
    if(GetCount() == 0)
    {
      number = auxNumber;
    }
    // If it's not the first input
    else
    {
      // Checks if positive
      if(GetNumber() > 0)
      {
        number = (GetNumber() * 10) + auxNumber;
      }
      // Checks if negative
      else
      {
        number = (GetNumber() * 10) - auxNumber;
      }
    }
  }

  count++;
}

void Number::ToggleDecimal()
{
  decimal = !decimal;
}

void Number::DisplayObject()
{
  lcd2.begin(16, 2);
//  if(decimal)
//  {
//    if(deciCount == 1)
//    {
//      lcd2.print(number, deciCount);
//    }
//    else
//    {
//      lcd2.print(number, deciCount - 1);
//    }
//  }
//  else
//  {
//    lcd2.print(number, 0);
//  }//END OF IF
  lcd2.clear();
  lcd2.setCursor(0, 0);
  lcd2.print(number);
}

float Number::GetNumber()
{
  return number;
}

const boolean Number::GetDecimal()
{
  return decimal;
}

const int Number::GetCount()
{
  return count;
}

const int Number::GetDeciCount()
{
  return deciCount;
}


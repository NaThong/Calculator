#include "Header.h"
LiquidCrystal lcd3(8,9,10,11,12,13);

Operation::Operation()
{
  Calculator::SetType('O');
  oper = 0;
}

Operation::~Operation(){}

void Operation::SetOper(int auxValue)
{
  oper = auxValue;
}

void Operation::DisplayObject()
{
  lcd3.begin(16, 2);
  String outputString;
  
  switch(oper)
  {
    case 1: outputString = "+";
            break;
    case 2: outputString = "-";
            break;
    case 3: outputString = "*";
            break;
    case 4: outputString = "/";
            break;
    case 5: outputString = "^";
            break;
    case 6: outputString = "(";
            break;
    case 7: outputString = ")";
  }
  
  lcd3.print(outputString);
}

int Operation::GetOper()
{
  return oper;
}

#ifndef HEADER_HEADER
#define HEADER_HEADER

#include "LiquidCrystal.h"
#include "Arduino.h"
#include "BinaryKeypad.h"
#include "Calculator.h"
#include "CalculatorList.h"
#include "Number.h"
#include "Operation.h"

#define ledpin 13

// Special characters that we'll use
//byte UP_ARROW [8] = 
//{
//  B00100,
//  B01110,
//  B11111,
//  B00100,
//  B00100,
//  B00100,
//  B00100,
//  B00100
//};
//
//byte POW_SYMBOL [8] =
//{
//  B00100,
//  B01010,
//  B10001,
//  B00000,
//  B00000,
//  B00000,
//  B00000,
//  B00000
//};

void showWelcome();

#endif

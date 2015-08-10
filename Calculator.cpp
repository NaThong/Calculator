#include "Header.h"

Calculator::Calculator()
{
  objectType = ' ';
  next       = NULL;
  prev       = NULL;
}

Calculator::~Calculator(){}

float Calculator::GetNumber(){}

void Calculator::SetNumber(float auxNumber){}

void Calculator::SetType(char auxChar)
{
  objectType = auxChar;
}

void Calculator::SetNext(Calculator *auxPtr)
{
  next = auxPtr;
}

void Calculator::SetPrev(Calculator *auxPtr)
{
  prev = auxPtr;
}

int Calculator::GetOper(){}

void Calculator::DisplayObject(){}

Calculator *Calculator::GetNext()
{
  return next;
}

Calculator *Calculator::GetPrev()
{
  return prev;
}

const char Calculator::GetType()
{
  return objectType;
}

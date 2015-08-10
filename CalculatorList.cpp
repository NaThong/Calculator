#include "Header.h"
LiquidCrystal lcd4(8,9,10,11,12,13);

CalculatorList::CalculatorList()
{
  tail  = NULL;
  head  = NULL;
  count = 0;
}

CalculatorList::~CalculatorList(){}

void CalculatorList::SetHead(Calculator *auxCalcPtr)
{
  head = auxCalcPtr;
}

void CalculatorList::SetTail(Calculator *auxCalcPtr)
{
  tail = auxCalcPtr;
}

void CalculatorList::AddToList(Calculator *auxCalcPtr)
{ 
  auxCalcPtr->SetNext(head);
  
  if(GetSize() > 0)
  {
    auxCalcPtr->GetNext()->SetPrev(auxCalcPtr);
  }
  else
  {
    tail = auxCalcPtr;
  }
  
  head = auxCalcPtr;
  count++;
  
  auxCalcPtr = NULL;
}

void CalculatorList::RemoveUnneededNodes(Calculator *auxPtr)
{
  auxPtr->GetNext()->SetPrev(auxPtr->GetPrev()->GetPrev());
  if(auxPtr->GetPrev()->GetPrev() != NULL)
  {
    auxPtr->GetPrev()->GetPrev()->SetNext(auxPtr->GetNext());
  }
  
  if(auxPtr->GetPrev() == GetHead())
  {
    SetHead(auxPtr->GetNext());
  }
  delete auxPtr->GetPrev();
  delete auxPtr;
  auxPtr = NULL;
  count = count - 2;
}

void CalculatorList::DeleteList()
{
  Calculator *auxCalcPtr;
  
  auxCalcPtr = head;
  
  while(auxCalcPtr != NULL)
  {
    if(auxCalcPtr->GetNext() == NULL)
    {
      delete auxCalcPtr;
      auxCalcPtr = NULL;
    }
    else
    {
      auxCalcPtr = auxCalcPtr->GetNext();
      delete auxCalcPtr->GetPrev();
    }
  }
  SetHead(NULL);
  SetTail(NULL);
}

Calculator *CalculatorList::SearchBackwardsAndReturnPtr(int auxNumber)
{
  int         auxNumTwo;
  boolean     found;
  Calculator *auxPtr;
  
  auxPtr = tail;
  found  = false;
  
  if(auxNumber == 1)
  {
    auxNumTwo = 2;
  }
  
  if(auxNumber == 3)
  {
    auxNumTwo = 4;
  }
  
  while(auxPtr != NULL && !found)
  {
    if(auxPtr->GetType() == 'O')
    {
      if(auxPtr->GetOper() == auxNumber || auxPtr->GetOper() == auxNumTwo)
      {
        found = true;
      }
      else
      {
        auxPtr = auxPtr->GetPrev();
      }
    }
    else
    {
      auxPtr = auxPtr->GetPrev();
    }
  }
  return auxPtr;
}
    
Calculator *CalculatorList::SearchAndReturnPtr(int auxNumber)
{
  boolean     found;
  Calculator *auxPtr;
  
  auxPtr = head;
  found  = false;
  
  while(auxPtr != NULL && !found)
  {
    if(auxPtr->GetType() == 'O')
    {
      if(auxPtr->GetOper() == auxNumber)
      {
        found = true;
      }
      else
      {
        auxPtr = auxPtr->GetNext();
      }
    }
    else
    {
      auxPtr = auxPtr->GetNext();
    }//END IF 
  }//END WHILE
  return auxPtr;
} 

int CalculatorList::SearchAndReturnParCount()
{
  lcd4.begin(16, 2);
  int         countOpen;
  int         countClose;
  Calculator *auxPtr;
  
  countOpen  = 0;
  countClose = 0;
  auxPtr     = GetHead();
  
  while(auxPtr != NULL)
  {
    if(auxPtr->GetType() == 'O')
    {
      if(auxPtr->GetOper() == 6)
      {
        countOpen++;
      }
      
      if(auxPtr->GetOper() == 7)
      {
        countClose++;
      }
    }
    auxPtr = auxPtr->GetNext();
  }
  
  if(countOpen != countClose)
  {
    lcd4.clear();
    lcd4.setCursor(0, 0);
    lcd4.print("Missing a ()");
    delay(2000);
  }
  return countOpen;
}

void CalculatorList::DisplayHead()
{
  lcd4.begin(16, 2);
  lcd4.clear();
  lcd4.setCursor(0, 0);
  head->DisplayObject();
}

void CalculatorList::DisplayList()
{
  lcd4.begin(16, 2);
  Calculator *auxPtr;
  auxPtr = head;
  
  while(auxPtr->GetNext() != NULL)
  {
    lcd4.clear();
    lcd4.setCursor(0, 0);
    auxPtr->DisplayObject();
    auxPtr = auxPtr->GetNext();
    delay(500);
  }
  lcd4.clear();
  lcd4.setCursor(0, 0);
  auxPtr->DisplayObject();
  delay(500);
  
  lcd4.clear();
  lcd4.setCursor(0, 0);
  lcd4.print("Backwards");
  delay(500);
  while(auxPtr != NULL)
  {
    lcd4.clear();
    lcd4.setCursor(0, 0);
    auxPtr->DisplayObject();
    auxPtr = auxPtr->GetPrev();
    delay(500);
  }
  lcd4.clear();
  lcd4.setCursor(0, 0);
  lcd4.print("Finished");
  delay(500);
}

Calculator *CalculatorList::GetHead()
{
  return head;
}

Calculator *CalculatorList::GetTail()
{
  return tail;
}

int CalculatorList::GetSize()
{
  return count;
}


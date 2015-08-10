#include "Header.h"
LiquidCrystal lcd(8,9,10,11,12,13);

int             parCount;
boolean         found;
BinaryKeypad    myKey;
CalculatorList  myList;
CalculatorList  myListTwo;
Number         *myNumber;
Operation      *myOper;
Calculator     *myCalc;
Calculator     *auxPtrOne;
Calculator     *auxPtrTwo;
Calculator     *auxPtrThree;

void setup()
{
  lcd.begin(16, 2);
  showWelcome();
  Serial.begin(9600);
}

void loop()
{
  myNumber = new Number;
  myOper   = new Operation;
  
  while(!myKey.GetSpecialChar())
  {
    myKey.SetKeyValue();
    
    if(!myKey.GetSpecialChar())
    {
      myNumber->CalculateNumber(myKey.GetKeyValue());
      lcd.clear();
      lcd.setCursor(0, 0);
      myNumber->DisplayObject();
    }
    else
    {
      switch(myKey.GetKeyValue())
      {
        /*******************************************************
         * FOR DECIMAL
         *******************************************************/
        case 16: myNumber->ToggleDecimal();
                 myNumber->DisplayObject();
                 myKey.ToggleSpecialChar();
                 break;
                 
        /*******************************************************
         * FOR NEGATING
         *******************************************************/
        case 17: // For negating number
                 break;
                 
        /*******************************************************
         * FOR OPERATION INPUT
         *******************************************************/
        case 18: lcd.clear();
                 lcd.setCursor(0, 0);
                 lcd.print("Enter Operator");
                 myKey.PauseUntilButtonReleased();
                 if(myNumber->GetDeciCount() != 1 || myNumber->GetCount() != 0)
                 {
                   myCalc   = myNumber;
                   myList.AddToList(myCalc); // Add previous number to the list
                   myNumber = NULL;
                   myCalc   = NULL;
                 }
                 myKey.SetKeyValue();
                 myOper->SetOper(myKey.GetKeyValue());
                 myCalc = myOper;
                 myList.AddToList(myCalc);     // Add operation to list
                 lcd.clear();
                 lcd.setCursor(0, 0);
                 myOper->DisplayObject();
                 myOper = NULL;
                 myCalc = NULL;
                 break;
                 
        /*******************************************************
         * FOR CLEARING INPUT
         *******************************************************/
        //case 20: // For clear button
        
        /*******************************************************
         * EQUAL BUTTON
         *******************************************************/
        case 24: if(myNumber->GetDeciCount() != 1 || myNumber->GetCount() != 0)
                 {
                   myCalc   = myNumber;
                   myList.AddToList(myCalc); // Add previous number to the list
                 }
                 myNumber = NULL;
                 myCalc   = NULL;
                 
                 parCount = myList.SearchAndReturnParCount();
                 
                 lcd.clear();
                 lcd.setCursor(0, 1);
                 lcd.print(parCount);
                 delay(2000);
                 
                 myList.DisplayList();
                 for(int index = 0; index < parCount; index++)
                 {
                   myCalc = myList.GetTail();
                   
                   while(myCalc != NULL)
                   {
                     if(myCalc->GetType() == 'O')
                     {
                       if(myCalc->GetOper() == 6)
                       {
                         auxPtrOne = myCalc;
                       }
                     }
                     myCalc = myCalc->GetPrev();
                   }
                   
                   myCalc = auxPtrOne->GetPrev();
                   
                   found = false;
                   
                   while(myCalc != NULL && !found)
                   {
                     if(myCalc->GetType() == 'O')
                     {
                       if(myCalc->GetOper() == 7)
                       {
                         found = true;
                       }
                       else
                       {
                         myCalc = myCalc->GetPrev();
                       }
                     }
                     else
                     {
                       myCalc = myCalc->GetPrev();
                     }
                   }
                   
                   auxPtrTwo = myCalc;
                   
                   if(myCalc == NULL)
                   {
                     lcd.clear();
                     lcd.setCursor(0, 0);
                     lcd.print("Cannot find ()");
                   }
                   auxPtrThree = auxPtrOne->GetPrev();
                   
                   if(found)
                   {
                     while(auxPtrThree != auxPtrTwo)
                     {
                       if(auxPtrThree->GetType() == 'N')
                       {
                         myNumber = NULL;
                         myNumber = new Number;
                         myNumber->SetNumber(auxPtrThree->GetNumber());
                         myCalc = myNumber;
                       }
                       else
                       {
                         myOper = NULL;
                         myOper = new Operation;
                         myOper->SetOper(auxPtrThree->GetOper());
                         myCalc = myOper;
                       }
                       myListTwo.AddToList(myCalc);
                       auxPtrThree = auxPtrThree->GetPrev();
                     }
                   }
/******************************************************************************************
 * THIS IS WHERE THE ISSUE SEEMS TO BE HAPPENING
 ******************************************************************************************/
                   /***************************************************************************************************************************************************
                    * Evaluation for ListTwo Beginning
                    ***************************************************************************************************************************************************/
                   /****************************************************
                    * EXPONENTS
                    ****************************************************/
                   myCalc = myListTwo.SearchAndReturnPtr(5);
  
                   while(myCalc != NULL)
                   {
                     myCalc->GetNext()->SetNumber(pow(myCalc->GetNext()->GetNumber(), myCalc->GetPrev()->GetNumber()));
                
                     myListTwo.RemoveUnneededNodes(myCalc);
                     
                     myCalc = myListTwo.SearchAndReturnPtr(5);              
                   }
  
                   /*************************************************************
                    * MULTIPLICATION AND DIVISION
                    *************************************************************/
                   myCalc = myListTwo.SearchBackwardsAndReturnPtr(3);
                   
                   while(myCalc != NULL)
                   {
                     if(myCalc->GetOper() == 3)
                     {
                       myCalc->GetNext()->SetNumber(myCalc->GetNext()->GetNumber() * myCalc->GetPrev()->GetNumber());
                     }
                     else
                     {
                       myCalc->GetNext()->SetNumber(myCalc->GetNext()->GetNumber() / myCalc->GetPrev()->GetNumber());
                     }
                     
                     myListTwo.RemoveUnneededNodes(myCalc);
  
                     myCalc = myListTwo.SearchBackwardsAndReturnPtr(3);
                   }
  
                   /**************************************************************
                    * ADDING AND SUBTRACTING
                    **************************************************************/
                   myCalc = myListTwo.SearchBackwardsAndReturnPtr(1);
                   
                   while(myCalc != NULL)
                   {
                     if(myCalc->GetOper() == 1)
                     {
                       myCalc->GetNext()->SetNumber(myCalc->GetNext()->GetNumber() + myCalc->GetPrev()->GetNumber());
                     }
                     else
                     {
                       myCalc->GetNext()->SetNumber(myCalc->GetNext()->GetNumber() - myCalc->GetPrev()->GetNumber());
                     }
                     
                     myListTwo.RemoveUnneededNodes(myCalc);
  
                     myCalc = myListTwo.SearchBackwardsAndReturnPtr(1);
                   }
                   /***************************************************************************************************************************************************
                    * Evaluation for ListTwo End
                    ***************************************************************************************************************************************************/
                   myNumber = NULL;
                   myNumber = new Number;
                   myNumber->SetNumber(myListTwo.GetHead()->GetNumber());
                   myListTwo.DisplayList();
                   lcd.clear();
                   lcd.setCursor(0, 0);
                   lcd.print("EVA LIST2 DONE");
                   delay(2000);
                   myNumber->DisplayObject();
                   delay(2000);
                   
                   if(auxPtrOne->GetNext() != NULL)
                   {
                     auxPtrOne->GetNext()->SetPrev(myNumber);
                   }
                   else
                   {
                     myList.SetTail(myNumber);
                   }
                   myNumber->SetNext(auxPtrOne->GetNext());
                   auxPtrOne->SetNext(NULL);
                   
                   if(auxPtrTwo->GetPrev() != NULL)
                   {
                     auxPtrTwo->GetPrev()->SetNext(myNumber);
                   }
                   else
                   {
                     myList.SetHead(myNumber);
                   }
                   myNumber->SetPrev(auxPtrTwo->GetPrev());
                   auxPtrTwo->SetPrev(NULL);
                   myListTwo.DeleteList();
                   
//                   while(auxPtrTwo != NULL)
//                   {
//                     if(auxPtrTwo->GetNext() != NULL)
//                     {
//                       auxPtrTwo = auxPtrTwo->GetNext();
//                       delete auxPtrTwo->GetPrev();
//                     }
//                     else
//                     {
//                       delete auxPtrTwo;
//                     }
//                   }
                       
                 }//END OF FOR LOOP
                 

                 myList.DisplayList();
                   delay(2000);
                 /******************************************************************************************************************************************
                  * Evaluation for Main List Beginning
                  ******************************************************************************************************************************************/
                 /****************************************************
                  * EXPONENTS
                  ****************************************************/
                 myCalc = myList.SearchAndReturnPtr(5);

                 while(myCalc != NULL)
                 {
                   myCalc->GetNext()->SetNumber(pow(myCalc->GetNext()->GetNumber(), myCalc->GetPrev()->GetNumber()));
              
                   myList.RemoveUnneededNodes(myCalc);
                   
                   myCalc = myList.SearchAndReturnPtr(5);              
                 }

                 /*************************************************************
                  * MULTIPLICATION AND DIVISION
                  *************************************************************/
                 myCalc = myList.SearchBackwardsAndReturnPtr(3);
                 
                 while(myCalc != NULL)
                 {
                   if(myCalc->GetOper() == 3)
                   {
                     myCalc->GetNext()->SetNumber(myCalc->GetNext()->GetNumber() * myCalc->GetPrev()->GetNumber());
                   }
                   else
                   {
                     myCalc->GetNext()->SetNumber(myCalc->GetNext()->GetNumber() / myCalc->GetPrev()->GetNumber());
                   }
                   
                   myList.RemoveUnneededNodes(myCalc);

                   myCalc = myList.SearchBackwardsAndReturnPtr(3);
                 }

                 /**************************************************************
                  * ADDING AND SUBTRACTING
                  **************************************************************/
                 myCalc = myList.SearchBackwardsAndReturnPtr(1);
                 
                 while(myCalc != NULL)
                 {
                   if(myCalc->GetOper() == 1)
                   {
                     myCalc->GetNext()->SetNumber(myCalc->GetNext()->GetNumber() + myCalc->GetPrev()->GetNumber());
                   }
                   else
                   {
                     myCalc->GetNext()->SetNumber(myCalc->GetNext()->GetNumber() - myCalc->GetPrev()->GetNumber());
                   }
                   
                   myList.RemoveUnneededNodes(myCalc);

                   myCalc = myList.SearchBackwardsAndReturnPtr(1);
                 }
                 /***********************************************************************************************************************************************
                  * Evaluation for Main List End
                  ***********************************************************************************************************************************************/
      }//END OF SWITCH
      
    }//END OF IF

    /***************************************************************
     * PAUSE
     ***************************************************************/
    myKey.PauseUntilButtonReleased();
  }//END OF WHILE LOOP
  
  myList.DisplayHead();
  myKey.ToggleSpecialChar();
}//END OF VOID LOOP













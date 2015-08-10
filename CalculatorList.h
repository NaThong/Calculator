#ifndef HEADER_CALCULATORLIST
#define HEADER_CALCULATORLIST

#include "Header.h"

class CalculatorList
{
  public:
    CalculatorList();
    ~CalculatorList();
    
    // Mutators
    void SetHead(Calculator *auxCalcPtr);
    void SetTail(Calculator *auxCalcPtr);
    void AddToList(Calculator *auxCalcPtr);
    void RemoveUnneededNodes(Calculator *auxPtr);
    void DeleteList();
    // Accessors
    Calculator *SearchBackwardsAndReturnPtr(int auxNumber);
    Calculator *SearchAndReturnPtr(int auxNumber);
    int         SearchAndReturnParCount();
    void        DisplayHead();
    void        DisplayList();
    Calculator *GetHead();
    Calculator *GetTail();
    int         GetSize();
    
  private:
    Calculator *tail;
    Calculator *head;
    int         count;
};

#endif

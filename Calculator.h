#ifndef HEADER_CALCULATOR
#define HEADER_CALCULATOR

#include "Header.h"

class Calculator
{
  public:
    Calculator();
    virtual ~Calculator();
    
    // Mutators
    virtual void SetNumber(float auxNumber);
    void SetType(char auxChar);
    void SetNext(Calculator *auxPtr);
    void SetPrev(Calculator *auxPtr);
    
    // Accessors
    virtual float  GetNumber();
    virtual int    GetOper();
    virtual void   DisplayObject();
    Calculator     *GetNext();
    Calculator     *GetPrev();
    const char     GetType();
    
  private:
    char       objectType;
    Calculator *next;
    Calculator *prev;
};

#endif

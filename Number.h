#ifndef HEADER_NUMBER
#define HEADER_NUMBER

#include "Header.h"

class Number: public Calculator
{
  public:
    Number();
    virtual ~Number();
    
    //Mutators
    virtual void SetNumber(float auxNumber);
    void CalculateNumber(int auxNumber);
    void ToggleDecimal();
    
    //Accessors
    virtual void   DisplayObject();
    virtual float  GetNumber();
    const boolean  GetDecimal();
    const int      GetDeciCount();
    const int      GetCount();
    
  private:
    float      number;
    boolean    decimal;
    int        count;
    int        deciCount;
};

#endif

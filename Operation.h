#ifndef HEADER_OPERATION
#define HEADER_OPERATION

#include "Header.h"

class Operation: public Calculator
{
  public:
    Operation();
    virtual ~Operation();
    
    //Mutators
    void SetOper(int auxValue);
    
    //Accessors
    virtual void DisplayObject();
    virtual int  GetOper();
    
  private:
    int  oper;
};

#endif
    

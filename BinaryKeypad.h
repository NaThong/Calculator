#ifndef HEADER_BINARYKEYPAD
#define HEADER_BINARYKEYPAD

#include "Header.h"

class BinaryKeypad
{
  public:
    BinaryKeypad();
    ~BinaryKeypad();
    
    // Mutators
    void SetKeyValue();             // Calculates the value of the key pressed
    void PauseUntilButtonPressed(); // Pauses until a button is pressed
    void PauseUntilButtonReleased();// Pauses until a button is released
    void ToggleSpecialChar();       // Toggles specialChar T/F
    
    // Accessors
    const int     GetKeyValue();    // Returns value
    const boolean GetSpecialChar(); // Returns specialChar
  
  private:
    int     buttonArray[5];
    int     value;
    boolean specialChar;
};

#endif

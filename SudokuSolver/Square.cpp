// Square.cpp
// Author: Kelsey Stemm
// Date: 11-30-15
// Description:
// Square is a subunit of Puzzle that holds an integer value and whether the
// value was determined at the beginning to be a part of the Puzzle (fixed).
// Square also contains static const variables that denote the values able
// to be used by Square.
// 
// Inputs: 
// -- Square values and whether the value is fixed within the puzzle
//
// Outputs:
// -- Can retrieve both the value and whether it is fixed
//
// Assumptions:
// -- Puzzle class takes care of all checking of numbers and when Squares 
//    should be fixed.
// 
// Major algorithms & key variables:
// Algorithms: None
// Key Variables: value, fixed
#include "Square.h"
#include <exception>
#include <stdexcept>
using namespace std;

//--------------------------------------------------------------------------
// Square(int val) 
// Constructor: Constructs a square object, initializes value and isFixed
// Preconditions: None
// Postconditions: Square object created
// Return value: None
// Functions called: None
Square::Square(int val) {
   value = val;
}
//--------------------------------------------------------------------------
// int getValue()
// Retrieves the value of the Square object
// Preconditions: Square exists
// Postconditions: None
// Return value: integer of the value
// Functions called: None
int Square::getValue() {
   return value;
}

//--------------------------------------------------------------------------
// bool isFixed()
// Retrieves fixed of the Square object
// Preconditions: Square exists
// Postconditions: None
// Return value: true if value is fixed, false if not fixed
// Functions called: None
bool Square::isFixed() {
   return fixed;
}

//--------------------------------------------------------------------------
// bool setFixedTrue()
// Set fixed of the Square object
// Preconditions: Square exists
// Postconditions: Sets fixed to true
// Return value: true if value is fixed, false if not fixed
// Functions called: None
bool Square::setFixedTrue() {
   fixed = true;
   return fixed;
}
//--------------------------------------------------------------------------
// bool setValue(int value);
// Sets the value of the Square object
// Preconditions: Square exists, value is an integer between 1-9
// Postconditions: Square object's value is changed
// Return value: Returns true if value is changed, false if otherwise
// Functions called: None
bool Square::setValue(const int setValue) {
   if (fixed) {
      return false;
   }
   value = setValue;
   return true;
}

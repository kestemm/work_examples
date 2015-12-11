// Puzzle.cpp
// Author: Kelsey Stemm
// Date: 11-30-15
// Description:
// A Puzzle consists of Squares in a range of values from MIN_VALUE to 
// MAX_VALUE, whereby each value can only exist once in a row, column (col),
// or block. EMPTY_VALUE denotes a Square whose value has yet to be set.
// Fixed Squares denote those values that were set upon input. Solving the 
// Puzzle will fill in all Squares, if solvable. 
//
// Inputs: 
// -- MAX_VALUE * MAX_VALUE characters for a Puzzle
//
// Outputs:
// -- If input of Puzzle is in incorrect Sudoku format, output where incorrect
//    first occurrence
// -- True/false if Puzzle is solved or not
//
// Assumptions:
// -- User will input at least the correct number of characters necessary to 
//    propagate a Puzzle
// -- When input is incorrect, stop reading in Puzzle. Output where error 
//    occurred.
//
// Major algorithms & key variables:
// Algorithms: None
// Key Variables: MIN_VALUE, MAX_VALUE, EMPTY_VALUE, BLOCK_SIDE
#include "Square.h"
#include "Puzzle.h"
#include <iostream>
using namespace std;

//--------------------------------------------------------------------------
// istream& operator>>(istream &input, Puzzle & newPuzzle)
// Overloaded >> operator: allows for input of entire Puzzle object
// Preconditions: Puzzle consisting of 81 Squares pointers
// Postconditions: All 81 pointers to Square objects
// Return value: Input
// Functions called: set, setFixedtoTrue
istream& operator>>(istream &input, Puzzle & newPuzzle) {
   char valChar;
   int valInt = -1; //unintitialized, cannot be 0
   // creating squares and inputting into thePuzzle
   for (int i = 0; i < Puzzle::MAX_VALUE; i++) {
      for (int j = 0; j < Puzzle::MAX_VALUE; j++) {
        // get a valid value from input
         while ((valInt > Puzzle::MAX_VALUE || valInt < Puzzle::MIN_VALUE)
            && valInt != Puzzle::EMPTY_VALUE) {
            valChar = input.get();
            valInt = valChar - 48;
         }
         // If the Puzzle can place a number there
         if (newPuzzle.set(i, j, valInt)) {
            if (valInt != Puzzle::EMPTY_VALUE) {
               newPuzzle.setFixedToTrue(i, j);
               newPuzzle.sizeInt--;
            }
         }
         else if(valInt != Puzzle::EMPTY_VALUE){
            cout << "Initial input:\n";
            newPuzzle.display();
            cout << endl;
            cout << "Your input is invalid at row " << i << " and col " 
               << j << ". Input has ceased. \nPlease change and try again.\n";
            exit(0);
         }
         valInt = -1; //need to reenter the while loop
      }
   }
   return input;
}

//--------------------------------------------------------------------------
// ostream& operator<<(ostream &output, const Puzzle & thePuzzle)
// Overloaded << operator: allows for output of entire Puzzle object
// Preconditions: Puzzle consisting of Squares pointers
// Postconditions: Puzzle unchanged, display all values without separators
// Return value: Output
// Functions called: None
ostream& operator<<(ostream &output, const Puzzle & thePuzzle) {
   for (int i = 0; i < Puzzle::MAX_VALUE; i++) {
      for (int j = 0; j < Puzzle::MAX_VALUE; j++) {
         cout << thePuzzle.puzArray[i][j]->getValue();
      }
   }
   return output;
}

//--------------------------------------------------------------------------
// Puzzle()
// Constructs a puzzle of Squares.
// Preconditions: None
// Postconditions: Puzzle consisting of 81 Square pointers
// Return value: None
// Functions called: None
Puzzle::Puzzle() {
   for (int i = 0; i < MAX_VALUE; i++) {
      for (int j = 0; j < MAX_VALUE; j++) {
         // Try to instantiate a Square with empty value
         try {
            puzArray[i][j] = new Square(EMPTY_VALUE);
         }
         catch (exception e) {
            cout << "You are out of memory.\n";
            exit(0);
         }
      }
   }
}

//--------------------------------------------------------------------------
// ~Puzzle()
// Destructs a puzzle of Squares.
// Preconditions: Puzzle consisting of 81 Square pointers
// Postconditions: Puzzle is destructed, including all Squares
// Return value: None
// Functions called: None
Puzzle::~Puzzle() {
   for (int i = 0; i < MAX_VALUE; i++) {
      for (int j = 0; j < MAX_VALUE; j++) {
         delete puzArray[i][j];
      }
   }
}

//--------------------------------------------------------------------------
// void display()
// Displays to the output stream the puzzle in an easily-readable format.
// Preconditions: Puzzle at any point during solving (empty to completely 
// solved.
// Postconditions: Puzzle is displayed.
// Return value: None
// Functions called: None
void Puzzle::display() {
   for (int i = 0; i < Puzzle::MAX_VALUE; i++) {
      for (int j = 0; j < Puzzle::MAX_VALUE; j++) {
         cout << puzArray[i][j]->getValue() << " ";
         // if the block is complete and it is not the end, print a side
         if ((j + 1) % Puzzle::BLOCK_SIDE == 0 &&
            (j + 1) != Puzzle::MAX_VALUE) {
            cout << "| ";
         }
      }
      // if the block is complete and it is not the end, print a side
      if ((i + 1) % Puzzle::BLOCK_SIDE == 0 &&
         (i + 1) != Puzzle::MAX_VALUE) {
         cout << "\n------+-------+------";
      }
      cout << endl;
   }
}

//--------------------------------------------------------------------------
// numEmpty()
// Determines the number of empty squares in a Puzzle
// Preconditions: Puzzle exists
// Postconditions: None
// Return value: Returns integer of number of empty Squares
// Functions called: getValue
int Puzzle::numEmpty() {
   int empty = 0;
   for (int i = 0; i < MAX_VALUE; i++) {
      for (int j = 0; j < MAX_VALUE; j++) {
         if (puzArray[i][j]->getValue() == 0) {
            empty++;
         }
      }
   }
   return empty;
}

//--------------------------------------------------------------------------
// size()
// Returns the original number of variable (not fixed) Squares in a Puzzle
// Preconditions: Puzzle exists
// Postconditions: None
// Return value: Returns integer of original number of blanks in a Puzzle
// Functions called: None
int Puzzle::size() {
   return sizeInt;
}

//--------------------------------------------------------------------------
// Square& const get(int row, int col)
// The get function retrieves the reference to a Square at x,y coordinates
// within the Puzzle
// Preconditions: Puzzle has been created
// Postconditions: Puzzle is unchanged
// Return value: A reference to the Square at that those coordinates
// Functions called: None
Square& Puzzle::get(const int row, const int col) const {
   Square& a = *puzArray[row][col];
   return a;
}

//--------------------------------------------------------------------------
// bool set(int row, int col, int value);
// The set function sets the value at row, col after checking that 
// the value to be set is valid. 
// Precondidtions: Puzzle exists, Square exists, Square can be set to value
// without breaking game rules.
// Postconditions: Square is changed to value.
// Return value: Returns true if value is changed, false if not
// Functions called: checkRow, checkCol, checkBlock, Square::setValue
bool Puzzle::set(const int row, const int col, const int value) {
   if (checkRow(row, value) && checkCol(col, value) && 
      checkBlock(row, col, value)) {
      puzArray[row][col]->setValue(value);
      return true;
   }
   return false;
}

//--------------------------------------------------------------------------
// bool setFixedToTrue(int row, int col);
// The set function sets the fixed at (row,col)
// Precondidtions: Puzzle exists, Square exists
// Postconditions: Square is fixed
// Return value: Returns true if fixed is changed, false if not
// Functions called: checkRow, checkCol, checkBlock, Square::setValue
bool Puzzle::setFixedToTrue(const int row, const int col) {
   bool fixed = puzArray[row][col]->setFixedTrue();
   return fixed;
}

//--------------------------------------------------------------------------
// bool remove(int row, int col)
// Removes a value from a square, replaces with 0.
// Preconditions: Puzzle exists, Square exists
// Postconditions: Square value at zero
// Return value: Returns true if remove successful, false if not
// Functions called: get
bool Puzzle::remove(const int row, const int col) {
   return puzArray[row][col]->setValue(0);
}

//--------------------------------------------------------------------------
// bool checkRow(int row, int value)
// Checks all values in the row of a Puzzle to see if the value given 
// already exists within that row.
// Preconditions: Puzzle exists
// Postconditions: Puzzle is unchanged
// Return value: Returns false if value is already present, true if not
// Functions called: get
bool Puzzle::checkRow(const int row, const int value) {
   for (int i = MIN_VALUE-1; i < MAX_VALUE; i++) {
      // if the value is already present in this row, then false
      if (puzArray[row][i]->getValue() == value) {
         return false;
      }
   }
   return true;
}

//--------------------------------------------------------------------------
// bool checkCol(int col, int value);
// Checks all values in the column of a Puzzle to see if the value given 
// already exists within that column.
// Preconditions: Puzzle exists
// Postconditions: Puzzle is unchanged
// Return value: Returns false if value is already present, true if not
// Functions called: get
bool Puzzle::checkCol(const int col, const int value) {
   for (int i = MIN_VALUE-1; i < MAX_VALUE; i++) {
      // if value is already present in the column, false
      if (puzArray[i][col]->getValue() == value) {
         return false;
      }
   }
   return true;
}

//--------------------------------------------------------------------------
// bool checkBlock(int row, int col, int value);
// Utilizes integer divison to determine what block the value exists in and
// begins at the top left box. Checks all values in the block of a Puzzle 
// to see if the value given already exists within that block.
// Preconditions: Puzzle exists
// Postconditions: Puzzle is unchanged
// Return value: Returns false if value is already present, true if not
// Functions called: get
bool Puzzle::checkBlock(const int row, const int col, const int value) {
   //find the Square to start in
   int rowStart = (row / BLOCK_SIDE) * BLOCK_SIDE;
   int colStart = (col / BLOCK_SIDE) * BLOCK_SIDE;
   //iterate through the 3x3 block, check if value is already present
   for (int i = rowStart; i < (rowStart + BLOCK_SIDE); i++) {
      for (int j = colStart; j < (colStart + BLOCK_SIDE); j++) {
         //if the value is present in the block, false
         if (puzArray[i][j]->getValue() == value) {
            return false;
         }
      }
   }
   return true;
}

//--------------------------------------------------------------------------
// bool solve(int row, int col);
// Utilizes recursive backtracking algorithm to solve Puzzle.
// Preconditions: Puzzle exists with 81 Square pointers (not null)
// Postconditions: Puzzle is solved, all values input
// Return value: Returns true if solved, false if not/unsolvable
// Functions called: nextSquare, solve
bool Puzzle::solve(int row, int col) {
   // base case: if over the row length or column length, then return true
   if (outOfBounds(row,col)) {
      return true;
   }
   // unable to change fixed values, find a value that is not Fixed
   while (puzArray[row][col]->isFixed()) {
      nextSquare(row, col);
      if (outOfBounds(row,col)) {
         return true;
      }
   }
   for (int i = MIN_VALUE; i <= MAX_VALUE; i++) {
      // if the value can be set, set it and attempt the next Square
      if (set(row, col, i)) {
         int nextRow = row, nextCol = col;
         nextSquare(nextRow, nextCol);
         //recursive call to the next Square in row and col
         if (solve(nextRow, nextCol)) {
            return true;
         }
         remove(row, col);
      }
   }
   return false;
}

//--------------------------------------------------------------------------
// bool nextSquare(int& row, int& col);
// Helper function to set a new row and/or column for a Puzzle class. 
// Preconditions: Ints row and col
// Postconditions: Row and col changed to new valid values
// Return value: None
// Functions called: None
void Puzzle::nextSquare(int& row, int& col) {
   // if at the end of the row, continue to the next row, first column
   // otherwise move over one column
   if (col == MAX_VALUE - 1) {
      row++;
      col = MIN_VALUE - 1;
   }
   else {
      col++;
   }
}

//--------------------------------------------------------------------------
// bool outOfBounds(int& row, int& col);
// Helper function to check the base case of being outside of the Puzzle.
// Preconditions: Ints row and col
// Postconditions: None
// Return value: Return true if out of bounds, 
// Functions called: None
bool Puzzle::outOfBounds(const int row, const int col) {
   // Check if the row and col being accessed is beyond the range of Puzzle
   if (row >= MAX_VALUE || col >= MAX_VALUE) {
      return true;
   }
   return false;
}

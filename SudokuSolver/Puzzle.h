// Puzzle.h
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
#pragma once
#include "Square.h"
#include <iostream>
using namespace std;

class Puzzle {
   //--------------------------------------------------------------------------
   // istream& operator>>(istream &input, Puzzle & newPuzzle)
   // Overloaded >> operator: allows for input of entire Puzzle object
   // Preconditions: Puzzle consisting of 81 Squares pointers
   // Postconditions: All 81 pointers to Square objects
   // Return value: Input
   // Functions called: None
   friend istream& operator>>(istream &input, Puzzle & thePuzzle);

   //--------------------------------------------------------------------------
   // ostream& operator<<(ostream &output, const Puzzle & thePuzzle)
   // Overloaded << operator: allows for output of entire Puzzle object
   // Preconditions: Puzzle consisting of 81 Squares pointers
   // Postconditions: Puzzle unchanged, display human-readable output
   // Return value: Output
   // Functions called: None
   friend ostream& operator<<(ostream &output, const Puzzle & thePuzzle);

public:
   static const int MIN_VALUE = 1;
   static const int MAX_VALUE = 9;
   static const int EMPTY_VALUE = 0;
   static const int BLOCK_SIDE = 3;

   //--------------------------------------------------------------------------
   // Puzzle()
   // Constructs a puzzle of Squares.
   // Preconditions: None
   // Postconditions: Puzzle consisting of 81 Square pointers
   // Return value: None
   // Functions called: None
   Puzzle();

   //--------------------------------------------------------------------------
   // ~Puzzle()
   // Destructs a puzzle of Squares.
   // Preconditions: Puzzle consisting of 81 Square pointers
   // Postconditions: Puzzle is destructed, including all Squares
   // Return value: None
   // Functions called: None
   ~Puzzle();

   //--------------------------------------------------------------------------
   // void display()
   // Displays to the output stream the puzzle in an easily-readable format.
   // Preconditions: Puzzle at any point during solving (empty to completely 
   // solved.
   // Postconditions: Puzzle is displayed.
   // Return value: None
   // Functions called: >> overload
   void display();

   //--------------------------------------------------------------------------
   // bool solve(int row, int col);
   // Utilizes recursive backtracking algorithm to solve Puzzle.
   // Preconditions: Puzzle exists with 81 Square pointers (not null)
   // Postconditions: Puzzle is solved, all values input
   // Return value: Returns true if solved, false if not/unsolvable
   // Functions called: nextSquare, solve
   bool solve(int row, int col);

   //--------------------------------------------------------------------------
   // numEmpty()
   // Determines the number of empty squares in a Puzzle
   // Preconditions: Puzzle exists
   // Postconditions: None
   // Return value: Returns integer of number of empty Squares
   // Functions called: getValue
   int numEmpty();

   //--------------------------------------------------------------------------
   // size()
   // Returns the original number of variable (not fixed) Squares in a Puzzle
   // Preconditions: Puzzle exists
   // Postconditions: None
   // Return value: Returns integer of original number of blanks in a Puzzle
   // Functions called: None
   int size();

private:
   Square* puzArray[MAX_VALUE][MAX_VALUE];
   int sizeInt = MAX_VALUE * MAX_VALUE;
   //--------------------------------------------------------------------------
   // Square& const get(int row, int col)
   // The get function retrieves the reference to a Square at row, col
   // within the Puzzle.
   // Preconditions: Puzzle has been created
   // Postconditions: Puzzle is unchanged
   // Return value: A reference to the Square at that those coordinates
   // Functions called: None
   Square& get(const int row, const int col) const;
   
   //--------------------------------------------------------------------------
   // bool set(int row, int col, int value);
   // The set function sets the value at row, col after checking that 
   // the value to be set is valid. 
   // Precondidtions: Puzzle exists, Square exists, Square can be set to value
   //    without breaking game rules.
   // Postconditions: Square is changed to value.
   // Return value: Returns true if value is changed, false if not
   // Functions called: checkRow, checkCol, checkBlock, Square::setValue
   bool set(const int row, const int col, int value);
   
   //--------------------------------------------------------------------------
   // bool setFixedToTrue(int row, int col);
   // The set function sets the fixed at (row,col)
   // Precondidtions: Puzzle exists, Square exists
   // Postconditions: Square is fixed
   // Return value: Returns true if fixed is changed, false if not
   // Functions called: checkRow, checkCol, checkBlock, Square::setValue
   bool setFixedToTrue(const int row, const int col);

   //--------------------------------------------------------------------------
   // bool remove(int row, int col)
   // Removes a value from a square, replaces with 0.
   // Preconditions: Puzzle exists, Square exists
   // Postconditions: Square value at zero
   // Return value: Returns true if remove successful, false if not
   // Functions called: get
   bool remove(const int row, const int col);

   //--------------------------------------------------------------------------
   // bool checkRow(int row, int value)
   // Checks all values in the row of a Puzzle to see if the value given 
   // already exists within that row.
   // Preconditions: Puzzle exists
   // Postconditions: Puzzle is unchanged
   // Return value: Returns true if value is already present, false if not
   // Functions called: get
   bool checkRow(const int row, const int value);
   
   //--------------------------------------------------------------------------
   // bool checkCol(int col, int value);
   // Checks all values in the column of a Puzzle to see if the value given 
   // already exists within that column.
   // Preconditions: Puzzle exists
   // Postconditions: Puzzle is unchanged
   // Return value: Returns true if value is already present, false if not
   // Functions called: get
   bool checkCol(const int col, const int value);
   
   //--------------------------------------------------------------------------
   // bool checkBlock(int row, int col, int value);
   // Utilizes integer divison to determine what block the value exists in and
   // begins at the top left box. Checks all values in the block of a Puzzle 
   // to see if the value given already exists within that block.
   // Preconditions: Puzzle exists
   // Postconditions: Puzzle is unchanged
   // Return value: Returns false if value is already present, true if not
   // Functions called: get
   bool checkBlock(const int row, const int col, const int value);
   
   //--------------------------------------------------------------------------
   // bool nextSquare(int& row, int& col);
   // Helper function to set a new row and/or column for a Puzzle class. 
   // Preconditions: Ints row and col
   // Postconditions: Row and col changed to new valid values
   // Return value: None
   // Functions called: None
   void nextSquare(int& row, int& col);

   //--------------------------------------------------------------------------
   // bool outOfBounds(int& row, int& col);
   // Helper function to check the base case of being outside of the Puzzle.
   // Preconditions: Ints row and col
   // Postconditions: None
   // Return value: Return true if out of bounds, 
   // Functions called: None
   bool outOfBounds(const int row, const int col);
};

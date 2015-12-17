// SudokuSolver (main)
// Author: Kelsey Stemm
// Date: 11-30-15
// Description:
// Sudoku is a game of placement of non-repeating numbers into a grid of rows
// columns (col) and blocks. This program solves these puzzles by:
// Creates a Sudoku puzzle object and reads in a Puzzle from cin. Program then
// displays the original, unsolved puzzle. Program then calls Puzzle::solve
// to solve the Puzzle. Program then displays the solved puzzle if solvable,
// or alerts user to Sudoku that is unsolvable.
// 
// Inputs: 
// -- Puzzle from cin
//
// Outputs:
// -- If input of Puzzle is in incorrect Sudoku format, output where incorrect
//    first occurrence (Puzzle)
// -- Puzzle in a human-readable format, unsolved
// -- Puzzle in a human-readable format, solved OR unsolvable
//
// Assumptions:
// -- All necessary values will be input, cin will wait until all characters
//    necessary are entered
// -- When input is incorrect, stop reading in Puzzle. Output where error 
//    occurred.
//
// Major algorithms & key variables:
// Algorithms: Backtracking recursive algorithm (Puzzle::solve)
// Key Variables: PuzzleSu
#include "Square.h"
#include "Puzzle.h"
#include <iostream>
using namespace std;

int main(){
   Puzzle sudoku;
   cin >> sudoku;
   cout << "Unsolved Puzzle:" << endl;
   sudoku.display();
   cout << endl;
   //Solve returns true if solved, false if not.
   if (sudoku.solve(0, 0)) {
      cout << "Solved Puzzle:" << endl;
      sudoku.display();
      cout << endl;
   }
   else {
      cout << "Puzzle is unsolvable." << endl;
   }
   return 0;
}

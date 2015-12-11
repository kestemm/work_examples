# Project Examples
Examples of projects from the Graduate Certificate in Computer Science. 
These were actual assignments and I in no way condone the use of these 
for cheating, see LICENSE. Feel free to help me improve them too!

**Sudoku Solver**

Description:
udoku is a game of placement of non-repeating numbers into a grid of rows,
columns (col) and blocks. This program solves these puzzles by:
Creating a Sudoku puzzle object and reading in a Puzzle from cin. Program then
displays the original, unsolved puzzle. Program then calls Puzzle::solve
to solve the Puzzle. Program then displays the solved puzzle if solvable,
or alerts user to Sudoku that is unsolvable.

Inputs: 
* Puzzle from cin of 81 digits from 0-9, by row (first row, second row...etc)

Outputs:
* If input of Puzzle is in incorrect Sudoku format, output where incorrect 
  first occurrence (Puzzle)
* Puzzle in a human-readable format, unsolved
* Puzzle in a human-readable format, solved OR unsolvable

Assumptions:
* All necessary values will be input, cin will wait until all characters
  necessary are entered
*When input is incorrect, stop reading in Puzzle. Output where error 
  occurred.

Major algorithms & key variables:
Algorithms: Backtracking recursive algorithm (Puzzle::solve)
Key Variables: Puzzle

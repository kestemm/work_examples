# Project Examples
Examples of projects from the Graduate Certificate in Computer Science. 
These were actual assignments and I in no way condone the use of these 
for cheating, see LICENSE. Feel free to help me improve them too!

**Concordance Generator**

Description:
A concordance generator reads in a body of text and outputs individual words
that occur within the body of text and gives context to when they are used, 
specifically the 5 preceeding and 5 subsequent words, when available.
Stop words are short words that generally do not have a context within a 
sentence, for example “a, ” “to”, or “or, ” which will be avoided.
Words are delimited by spaces and may contain within the word punctuation.
Keywords are not punctuation only and any trailing punctuation will be 
eliminated.

Inputs: 
The program’s input data is any.txt file, and will be read as ASCII letters.
* Delimiters can be spaces, tabs, or end lines.
* Empty files will have no concordance data.
* Files with only punctuation will also have no concordance data.
* Capitalization will not cause words to be considered to be different, 
  e.g.“fox” and “Fox” are  the same words.
* Numbers are included as words.
* Punctuation-only words are not keywords, but are considered to be
  contextual and will be treated as words for the pre- and post-keyword
  concordances.

Outputs:
Concordance output format follows a Key Word in Context(KWIC) style whereby 
the key words are shown surrounded by the two 5 - word sets :

|  The quick brown | fox | jumps over the lazy dog    |

|    What does the | fox |	say ? Ring ding ding ding |

Assumptions:
* ASCII characters only in file
* stopWords.txt may or may not exists within the directory
* File to utilize is accepted as a command line argument only

Major algorithms & key variables:
* Algorithms: Recursive binary tree search
* Key Variables: ifstream inFile, ReadIn toRead, BST theTree

******************************************************************************
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
* When input is incorrect, stop reading in Puzzle. Output where error 
  occurred.

Major algorithms & key variables:
* Algorithms: Backtracking recursive algorithm (Puzzle::solve)
* Key Variables: Puzzle

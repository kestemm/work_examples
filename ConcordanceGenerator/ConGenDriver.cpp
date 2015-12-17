// ConGenDriver.cpp
// Author: Kelsey Stemm
// Date: 12-9-15
// Description:
// A concordance generator reads in a body of text and outputs individual words
// that occur within the body of text and gives context to when they are used, 
// specifically the 5 preceeding and 5 subsequent words, when available.
// Stop words are short words that generally do not have a context within a 
// sentence, for example “a, ” “to”, or “or, ” which will be avoided.
// Words are delimited by spaces and may contain within the word punctuation.
// Keywords are not punctuation only and any trailing punctuation will be 
// eliminated.
//
// Inputs: 
// The program’s input data is any.txt file, and will be read as ASCII letters.
// -- Delimiters can be spaces, tabs, or end lines.
// -- Empty files will have no concordance data.
// -- Files with only punctuation will also have no concordance data.
// -- Capitalization will not cause words to be considered to be different, 
//    e.g.“fox” and “Fox” are  the same words.
// -- Numbers are included as words.
// -- Punctuation-only words are not keywords, but are considered to be
//    contextual and will be treated as words for the pre- and post-keyword
//    concordances.
//
// Outputs:
// Concordance output format follows a Key Word in Context(KWIC) style whereby 
// the key words are shown surrounded by the two 5 - word sets :
// |  The quick brown | fox | jumps over the lazy dog   |
// |    What does the |	fox |	say ? Ring ding ding ding |
//
// Assumptions:
// -- ASCII characters only in file
// -- stopWords.txt may or may not exists within the directory
// -- File to utilize is accepted as a command line argument only
// 
// Major algorithms & key variables:
// Algorithms: Recursive binary tree search
// Key Variables: ifstream inFile, ReadIn toRead, BST theTree


#include "LinkedList.h"
#include "BST.h"
#include "ReadIn.h"
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
   if (argc == 2) {
      ifstream inFile(argv[1]);
      ReadIn toRead;
      BST theTree;
      toRead.buildTree(inFile, theTree);
      theTree.displayTree();
      return 0;
   }
   else {
      cout << "Incorrect command line args, please list your text.txt file.";
   }
   return 0;
}


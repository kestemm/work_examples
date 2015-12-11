// ReadIn.h
// Author: Kelsey Stemm
// Date: 12-9-15
// Description:
// ReadIn accepts input from a file to create concordances for the BST. This
// program also takes the input and trims away unnecessary punctuation from
// the keyword only. This will also propagate a stopWords BST for comparison
// to keywords. If the keyword is a stopword, it will not be input into the
// BST as a keyword. The concordance is assembled based on the number of
// WORDS_IN_CONCORD, by utilizing a LinkedList<ReadInto> where ReadInto holds
// a single word. Three LinkedLists can exist at any given time: the 
// concordance for before the keyword (pre), the concordance after (post) and
// all of the remaining words in the document (all).
// 
// Inputs: 
// -- An in file stream
//
// Outputs:
// -- A BST containing all keywords and their concordances
//
// Assumptions:
// -- File to be read in can only have ASCII characters, will have issues with
//    non-ASCII charaters
// 
// Major algorithms & key variables:
// Algorithms: None
// Key Variables: ifstream inFile; LinkedList<ReadInto> pre, post, all;
//                BST stopWords, int WORDS_IN_CONCORD

#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include "LinkedList.h"
#include "BST.h"
using namespace std;

class ReadIn {

private:
   struct ReadInto {
      string wordUntrimmed;
   };
   string key;
   string preAssembled;
   string postAssembled;
   LinkedList<ReadInto> pre;
   LinkedList<ReadInto> post;
   LinkedList <ReadInto> all;
   BST stopWords;

public:
   static const int WORDS_IN_CONCORD = 5;

   //--------------------------------------------------------------------------
   // ReadIn();
   // Constructor for ReadIn
   // Preconditions: Memory available
   // Postconditions: All LinkedLists constructed and strings initialized to ""
   // Return value: None
   // Functions called: None
   ReadIn();

   //--------------------------------------------------------------------------
   // string generateCon(const LinkedList<ReadInto>& toAssemble);
   // Generates a single string from a LinkedList<ReadInto>. Separates them
   // with a single space.
   // Preconditions: LinkedList exists
   // Postconditions: LinkedList unchanged
   // Return value: A string of the concatenated word set
   // Functions called: None
   string generateCon(const LinkedList<ReadInto>& toAssemble);

   //--------------------------------------------------------------------------
   // bool isStopWord(const string toCheck);
   // When the BST stopWords does not exist, will assemble it. Then will 
   // search the BST for the word.
   // Preconditions: Memory exists for the BST, stopwords.txt available
   // Postconditions: BST stopWords exist
   // Return value: True if toCheck is a stopWord, false if not
   // Functions called: searchBST
   bool isStopWord(const string toCheck);

   //--------------------------------------------------------------------------
   // string trimWord(const string toTrim);
   // Takes an untrimmed word and removes all non-alphanumeric characters from
   // the end of the word. If the word is only non-alphanumeric, will remove
   // word entirely.
   // Preconditions: String exists
   // Postconditions: toTrim unchanged
   // Return value: Trimmed string
   // Functions called: None
   string trimWord(const string toTrim);

   //--------------------------------------------------------------------------
   // void getWords(ifstream & inFile);
   // Retrieves all of the words from inFile delimited by whitespace. Makes a
   // new ReadInto for all words in the file and places into LinkedList all.
   // Preconditions: LinkedList all is empty
   // Postconditions: LinkedList all contains all words in file
   // Return value: None
   // Functions called: None
   void getWords(ifstream & inFile);

   //--------------------------------------------------------------------------
   // void buildTree(ifstream & inFile, BST& theTree);
   // Builds the LinkedLists pre, post, all containing the words within the
   // inFile. For each word, create a pre- and post-keyword concordance and 
   // trim the keyword of all excess punctuation. Then adds a BSTNode to the
   // given BST.
   // Preconditions: inFile has text, BST exists
   // Postconditions: BST has BSTNodes corresponding to the words in the file
   // Return value: None
   // Functions called: getWords, addLast, addLastNode, trimWord, isStopWord
   //                   removeFirst
   void buildTree(ifstream & inFile, BST& theTree);
};

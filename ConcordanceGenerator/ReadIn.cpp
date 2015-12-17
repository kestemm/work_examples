// ReadIn.cpp
// Author: Kelsey Stemm
// Date: 12-9-15
// Description:
// ReadIn accepts input from a file to create concordances for the BST. This
// program also takes the input and trims away unnecessary punctuation from
// the keyword only. This will also propagate a stopWords BST for comparison
// to keywords. If the keyword is a stopword, it will not be input into the
// BST as a keyword.The concordance is assembled based on the number of
// WORDS_IN_CONCORD.
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
//                BST stopWords

#include "ReadIn.h"

//--------------------------------------------------------------------------
// ReadIn();
// Constructor for ReadIn
// Preconditions: Memory available
// Postconditions: All LinkedLists constructed and strings initialized to ""
// Return value: None
// Functions called: None
ReadIn::ReadIn() {
   pre.head = nullptr;
   pre.tail = nullptr;
   post.head = nullptr;
   post.tail = nullptr;
   key = "";
   preAssembled = "";
   postAssembled = "";
}

//--------------------------------------------------------------------------
// string generateCon(const LinkedList<ReadInto>& toAssemble);
// Generates a single string from a LinkedList<ReadInto>. Separates them
// with a single space.
// Preconditions: LinkedList exists
// Postconditions: LinkedList unchanged
// Return value: A string of the concatenated word set
// Functions called: None
string ReadIn::generateCon(const LinkedList<ReadInto>& toAssemble) {
   LinkedList<ReadInto>::Node* current = toAssemble.head;
   string toReturn;
   while (current != nullptr) {
      string word = current->data->wordUntrimmed;
      toReturn.append(word);
      toReturn.append(" ");
      current = current->next;
   }
   return toReturn;
}

//--------------------------------------------------------------------------
// bool isStopWord(const string toCheck);
// When the BST stopWords does not exist, will assemble it. Then will 
// search the BST for the word.
// Preconditions: Memory exists for the BST, stopwords.txt available
// Postconditions: BST stopWords exist
// Return value: True if toCheck is a stopWord, false if not
// Functions called: searchBST
bool ReadIn::isStopWord(const string toCheck) {
   if (stopWords.isEmpty()) {
      ifstream stopWordFile;
      stopWordFile.open("stopwords.txt");
      if (stopWordFile.is_open()) {
         string word = "";
         while (stopWordFile >> word) {
            for (int i = 0; i < word.length(); i++) {
               word[i] = tolower(word[i]);
            }
            stopWords.addBSTNode(word, "", "");
         }
      }
      // in the event that there is no data, no file and empty word once
      // trimming is complete
      stopWords.addBSTNode("", "", "");
   }
   return stopWords.searchBSTKey(toCheck);

}

//--------------------------------------------------------------------------
// string trimWord(const string toTrim);
// Takes an untrimmed word and removes all non-alphanumeric characters from
// the end of the word. If the word is only non-alphanumeric, will remove
// word entirely.
// Preconditions: String exists
// Postconditions: toTrim unchanged
// Return value: Trimmed string
// Functions called: None
string ReadIn::trimWord(const string toTrim) {
   string toReturn = toTrim;
   char lastChar;
   // while it is not an empty string
   while (toReturn != ""){
      lastChar = toReturn[toReturn.length() - 1];
      if (!isalpha(lastChar) && !isdigit(lastChar)) {
         toReturn = toReturn.substr(0, toReturn.length() - 1);     
      }  //will break when there is nothing left to change
      else {
         break;
      }
   }
   
   for (int i = 0; i < toReturn.length(); i++) {
      toReturn[i] = tolower(toReturn[i]);
   }
   return toReturn;
}

//--------------------------------------------------------------------------
// void getWords(ifstream & inFile);
// Retrieves all of the words from inFile delimited by whitespace. Makes a
// new ReadInto for all words in the file and places into LinkedList all.
// Preconditions: LinkedList all is empty
// Postconditions: LinkedList all contains all words in file
// Return value: None
// Functions called: None
void ReadIn::getWords(ifstream & inFile) {
   string word = "";
   while (inFile >> word) {
      try {
         ReadInto* newNode = new ReadInto;
         newNode->wordUntrimmed = word;
         all.addLast(newNode);
      }
      catch (...) {
         cout << "You are out of memory.\n";
         exit(0);
      }
   }
}

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
void ReadIn::buildTree(ifstream &  inFile, BST& theTree) {
   LinkedList<ReadInto>::Node* theKey;
   // build the LinkedList of all words
   getWords(inFile);
   // initialize the pre- and post-keyword concordance arrays (does not 
   // initialize key) based on size WORDS_IN_CONCORD
   for (int i = 0; i < WORDS_IN_CONCORD; i++) {
      if (all.isEmpty()) {
         break;
      }
      ReadInto* newPreNode = new ReadInto;
      newPreNode->wordUntrimmed = "";
      pre.addLast(newPreNode);
      post.addLastNode(all.removeFirst());
   }
   while (!post.isEmpty()) {                                            
      // pre and post exist, no key exists. Add another node from all. 
      // pull the key from the beginning of the post words. Generate and 
      // assemble the key and the pre- and post-keyword concordances.
      // Finally, move the key and remove/delete the first node.
      if (!all.isEmpty()) {
         post.addLastNode(all.removeFirst());
      }
      theKey = post.removeFirst();
      key = trimWord(theKey->data->wordUntrimmed);
      // if the key is not a stop word, then make a BST node
      if (!isStopWord(key)) {
         preAssembled = generateCon(pre);
         postAssembled = generateCon(post);
         theTree.addBSTNode(key, preAssembled, postAssembled);
      }
      pre.addLastNode(theKey);
      LinkedList<ReadInto>::Node* toDelete = pre.removeFirst();
      delete toDelete->data;
      delete toDelete;
   }
}

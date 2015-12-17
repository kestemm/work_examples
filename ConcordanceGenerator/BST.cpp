// BST.cpp
// Author: Kelsey Stemm
// Date: 
// Description:
// This binary search tree is composed of BSTNodes that have a string keyword, 
// a LinkedList<PrePost> where PrePost contain the concordance in the form
// of two strings, and a left and a right pointer to subtrees. The parts of 
// this produce a concordance, whereby a reader may know the preceeding and 
// subsequent words around a keyword. Displaying the keyword will be
// truncated to size KEYWORD_WIDTH and preKey and postKey concordance
// will be truncated to size CONCORD_WIDTH.
// 
// Inputs: 
// -- PrePost objects of preKey and postKeys
// -- BSTNodes containing a string, LinkedList<PrePost>, and two BSTNode*
//
// Outputs:
// -- Displaying the entire tree including each BSTNode and for each the 
//    corresponding LinkedList<PrePost>.
//
// Assumptions:
// -- BSTNodes have correct data input
// 
// Major algorithms & key variables:
// Algorithms: searching a binary search tree
// Key Variables: string keyword, preKey, postKey; LinkedList<PrePost> concord,
// CONCORD_WITDH

#include "BST.h"
#include <iomanip>

//--------------------------------------------------------------------------
// BST();
// BST constructor
// Preconditions: Memory available, does not exist
// Postconditions: Root is now nullptr
// Return value: None
// Functions called: None
BST::BST() {
   root = nullptr;
}

//--------------------------------------------------------------------------
// ~BST();
// Destructs BST
// Preconditions: BST exists
// Postconditions: BST does not exist
// Return value: None
// Functions called: destroyTree()
BST::~BST() {
   if (isEmpty()) { return; }
   destroyTree(root);
}

//--------------------------------------------------------------------------
// void destroyTree(BSTNode* subTreePtr);
// Taken from Carrano et al.: method used to destruct a BST
// Preconditions: BST exists
// Postconditions: BST is destructed
// Return value: None
// Functions called: Recursive call to itself
void BST::destroyTree(BSTNode* subTreePtr) {
   if (subTreePtr != nullptr)
   {
      destroyTree(subTreePtr->left);
      destroyTree(subTreePtr->right);
      delete subTreePtr;
   }
} 

//--------------------------------------------------------------------------
// void displayTree();
// Display all the BST's key with all concordances within the 
// LinkedList<PrePost>
// Preconditions: BST exists
// Postconditions: BST unchanged
// Return value: Outputs the entire 
// Functions called: display()
void BST::displayTree() {
   display(root);
}

//--------------------------------------------------------------------------
// void display(BSTNode* root);
// Display the key with all concordances within the LinkedList<PrePost>
// Preconditions: BST exists
// Postconditions: BST unchanged
// Return value: Outputs the entire 
// Functions called: Recursive call to itself
void BST::display (const BSTNode* top) {
   if (top != nullptr) {
      display(top->left);
      //display the linked list with the key in the middle
      string keyToPrint = top->keyword;  
      // Must cast the length as a signed int, as .length() returns an 
      // unsigned int (size_t) and C++ makes the assumption that 
      // resulting int of the subtraction is unsigned and then allows 
      // bit shift on unsigned ints. This causes a drop of the signed 
      // bit and thus incredibly high, positive numSpaces which will 
      // then attempt to add billions of spaces in the next for loop. 
      // Therefore, MUST CAST.
      int numSpaces = (KEYWORD_WIDTH - int(top->keyword.length())) / 2;
      // for centering purposes, append the end of the string with half of 
      // the difference in length between this and output.
      for (int i = 0; i < numSpaces; i++) {
         keyToPrint.append(" ");
      }
      // if the keyword won't fit into the width, then truncate
      if (top->keyword.length() > KEYWORD_WIDTH) {
         keyToPrint = top->keyword.substr(0, KEYWORD_WIDTH-1);
      }

      //display the pre and post key as first CONCORD_WIDTH characters
      LinkedList<PrePost>::Node* current;
      current = top->concord.head;
      string preConcord;
      string postConcord;
      // go through the entire LinkedList that is concordance and print
      // all concordances for that key
      while (current!=nullptr) {
         preConcord = current->data->preKey;
         postConcord = current->data->postKey;
         if (preConcord.length() > CONCORD_WIDTH) {
            preConcord = preConcord.substr(0, CONCORD_WIDTH - 1);
         }
         if (postConcord.length() > CONCORD_WIDTH) {
            postConcord = postConcord.substr(0, CONCORD_WIDTH - 1);
         }
         cout << "|" << right << setw(CONCORD_WIDTH) << preConcord;
         cout << "|" << setw(KEYWORD_WIDTH) << keyToPrint;
         cout << "|" << left << setw(CONCORD_WIDTH) << postConcord;
         cout << "|" << endl;
         current = current->next;
      }
      display(top->right);
   }
}

//--------------------------------------------------------------------------
// bool addBSTNode(string toAdd, string pre, string post);
// Adds BSTNode to the tree
// Preconditions: BST exists
// Postconditions: One BSTNode has been added
// Return value: None -- will break if out of memory
// Functions called: newBSTNode()
void BST::addBSTNode(string toAdd, string pre, string post) {
   PrePost* newData = new PrePost;
   newData->preKey = pre;
   newData->postKey = post;
   if (isEmpty()) {
      BSTNode* newNode = newBSTNode(toAdd, newData);
      root = newNode;
   } 
   else {
      BSTNode* toInsert = searchBST(root, toAdd);
      //check to see if node already there
      if (toAdd == toInsert->keyword) {
         toInsert->concord.addLast(newData);
      }
      //check if less than, left insert
      else if (toAdd < toInsert->keyword) {
         BSTNode* newNode = newBSTNode(toAdd, newData);
         toInsert->left = newNode;
      }
      //otherwise, right insert
      else {
         BSTNode* newNode = newBSTNode(toAdd, newData);
         toInsert->right = newNode;
      }
   }
}

//--------------------------------------------------------------------------
// BSTNode* searchBST(BSTNode* BSTRoot, const string keyword);
// Searches the BSTNode BSTRoot to determine if a keyword exists. If it 
// exists, then return a pointer to that node. However, if it doesn't exist,
// return a pointer to the parent. Thus, must check while exiting which 
// node is being returned.
// Preconditions: BST exists
// Postconditions: BST is unchanged
// Return value: BSTNode
// Functions called: Recursively calls itself
BST::BSTNode* BST::searchBST( BSTNode* BSTroot, string keyword) {
   // base case
   if (isEmpty()) { 
      return BSTroot; 
   }
   //base case 2: if equal, will also return.
   else if (keyword == BSTroot->keyword){
      return BSTroot;
   }
   //recursive left calls
   else if (keyword < BSTroot->keyword) {
      if (BSTroot->left == nullptr) { 
         return BSTroot; 
      }
      return searchBST(BSTroot->left, keyword);
   }
   //recursive right calls
   else {
      if (BSTroot->right == nullptr) { 
         return BSTroot; 
      }
      return searchBST(BSTroot->right, keyword);
   }
   return nullptr;
}

//--------------------------------------------------------------------------
// bool searchBSTKey(const string keyword);
// Searches the BST in-order to find the keyword.
// Preconditions: BST exists 
// Postconditions: BST unchanged
// Return value: True if keyword is found, false if otherwise
// Functions called: searchBST()
bool BST::searchBSTKey(const string keyword) {
   BSTNode* toCheck = searchBST(root, keyword);
   if (toCheck->keyword == keyword){
      return true;
   }
   return false;
}

//--------------------------------------------------------------------------
// bool isEmpty();
// Checks if the BST is empty
// Preconditions: BST exists
// Postconditions: BST unchanged
// Return value: True if empty, false if otherwise
// Functions called: None
bool BST::isEmpty() {
   return root == nullptr;
}

//--------------------------------------------------------------------------
// BSTNode* newBSTNode(string toAdd, PrePost* newData);
// Creates a BSTNode with PrePost data
// Preconditions: Memory available
// Postconditions: BSTNode created
// Return value: BSTNode* (will quit if out of memory)
// Functions called: None
BST::BSTNode* BST::newBSTNode(string toAdd, PrePost* newData) {
   try {
      BSTNode* newBSTNode = new BSTNode;
      newBSTNode->keyword = toAdd;
      newBSTNode->concord.addLast(newData);
      return newBSTNode;
   }
   catch (...) {
      cout << "You are out of memory.\n";
      exit(0);
   }
}

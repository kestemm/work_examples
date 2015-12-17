// BST.h
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

#pragma once
#include "LinkedList.h"
#include <string>
#include <iostream>
#include <exception>
using namespace std;

class BST {
   static const int CONCORD_WIDTH = 30;
   static const int KEYWORD_WIDTH = 16;

private:
   struct PrePost {
      string preKey;
      string postKey;
   };
   struct BSTNode {
      string keyword;
      LinkedList<PrePost> concord;
      BSTNode* right = nullptr;
      BSTNode* left = nullptr;
   };

   BSTNode* root;

   //--------------------------------------------------------------------------
   // BSTNode* newBSTNode(string toAdd, PrePost* newData);
   // Creates a BSTNode with PrePost data
   // Preconditions: Memory available
   // Postconditions: BSTNode created
   // Return value: BSTNode* (will quit if out of memory)
   // Functions called: None
   BSTNode* newBSTNode(string ToAdd, PrePost* newData);

   //--------------------------------------------------------------------------
   // void destroyTree(BSTNode* subTreePtr);
   // Taken from Carrano et al.: method used to destruct a BST
   // Preconditions: BST exists
   // Postconditions: BST is destructed
   // Return value: None
   // Functions called: Recursive call to itself
   void destroyTree(BSTNode* subTreePtr);

   //--------------------------------------------------------------------------
   // void display(BSTNode* root);
   // Display the key with all concordances within the LinkedList<PrePost>
   // Preconditions: BST exists
   // Postconditions: BST unchanged
   // Return value: Outputs the entire 
   // Functions called: Recursive call to itself
   void display (const BSTNode* top);

public:

   //--------------------------------------------------------------------------
   // BST();
   // BST constructor
   // Preconditions: Memory available, does not exist
   // Postconditions: Root is now nullptr
   // Return value: None
   // Functions called: None
   BST();

   //--------------------------------------------------------------------------
   // ~BST();
   // Destructs BST
   // Preconditions: BST exists
   // Postconditions: BST does not exist
   // Return value: None
   // Functions called: destroyTree()
   ~BST();

   //--------------------------------------------------------------------------
   // void displayTree();
   // Display all the BST's key with all concordances within the 
   // LinkedList<PrePost>
   // Preconditions: BST exists
   // Postconditions: BST unchanged
   // Return value: Outputs the entire 
   // Functions called: display()
   void displayTree();

   //--------------------------------------------------------------------------
   // bool isEmpty();
   // Checks if the BST is empty
   // Preconditions: BST exists
   // Postconditions: BST unchanged
   // Return value: True if empty, false if otherwise
   // Functions called: None
   bool isEmpty();

   //--------------------------------------------------------------------------
   // bool addBSTNode(string toAdd, string pre, string post);
   // Adds BSTNode to the tree
   // Preconditions: BST exists
   // Postconditions: One BSTNode has been added
   // Return value: None -- will quit if out of memory (based on newBSTNode())
   // Functions called: newBSTNode()
   void addBSTNode(string toAdd, string pre, string post);

   //--------------------------------------------------------------------------
   // bool searchBSTKey(const string keyword);
   // Searches the BST in-order to find the keyword.
   // Preconditions: BST exists 
   // Postconditions: BST unchanged
   // Return value: True if keyword is found, false if otherwise
   // Functions called: searchBST()
   bool searchBSTKey(const string keyword);

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
   BSTNode* searchBST( BSTNode* BSTRoot, const string keyword);
};


// LinkedList.h
// Author: Kelsey Stemm
// Date: 12-9-15
// Description:
// This LinkedList allows for first in, first out (FIFO) access to the list
// and had both a head and tail pointer. The function for addLast() will add 
// to the end and the removeFirst() function will remove from the beginning.
// 
// Inputs: 
// -- Nodes of type Data
//
// Outputs:
// -- Nodes of type Data
// -- Data
// -- Bools for adding/removing
//
// Assumptions:
// -- Data is a valid data type
// 
// Major algorithms & key variables:
// Algorithms: None
// Key Variables: Data

#pragma once
#include <iostream>
#include <exception>
using namespace std;

template <typename Data>
class LinkedList {
   friend class BST;
   friend class ReadIn;
private:
   struct Node {
      Data* data;
      Node* next;
   };
   Node* head;
   Node* tail;

   //--------------------------------------------------------------------------
   // Node* newNode(Data* newData)
   // Creates a new Node with Data type
   // Preconditions: Data is valid
   // Postconditions: new Node created with type Data
   // Return value: Node* 
   // Functions called: None
   Node* newNode(Data* newData);

public:

   //--------------------------------------------------------------------------
   // LinkedList();
   // Constructor for a LinkedList
   // Preconditions: Memory available
   // Postconditions: New LinkedList with head & tail set to nullptr
   // Return value: None
   // Functions called: None
   LinkedList();

   //--------------------------------------------------------------------------
   // ~LinkedList();
   // Destructor for LinkedList. 
   // Preconditions: LinkedList
   // Postconditions: LinkedList destructed with no memory leaks
   // Return value: None
   // Functions called: None
   ~LinkedList();

   //--------------------------------------------------------------------------
   // bool addLast(Data*)
   // Preconditions: Data* exists
   // Postconditions: LinkedList exists and has at least one Node with type
   // Data of toAdd, where toAdd is last in the LinkedList.
   // Return value: bool: true if added, false otherwise
   // Functions called: newNode
   void addLast(Data* toAdd);

   //--------------------------------------------------------------------------
   // bool addLastNode(Node* toAdd);
   // Preconditions: Node* exists
   // Postconditions: LinkedList exists and has at least one Node with type
   // Data of toAdd, where toAdd is last in the LinkedList.
   // Return value: bool: true if added, false otherwise
   // Functions called: newNode
   void addLastNode(Node* toAdd);

   //--------------------------------------------------------------------------
   // Node* removeFirst();
   // Preconditions: LinkedList with at least one Node exists
   // Postconditions: LinkedList with the first node removed
   // Return value: Node*
   // Functions called: None
   Node* removeFirst();

   //--------------------------------------------------------------------------
   // Data* getData(Node* aNode)
   // Preconditions: LinkedList exists with a Node. 
   // Postconditions: No change to LinkedList
   // Return value: Data value from within a Node
   // Functions called: None.
   Data* getData(Node* aNode);

   //--------------------------------------------------------------------------
   // bool isEmpty() const;
   // Preconditions: LinkedList exists
   // Postconditions: LinkedList is unchanged
   // Return value: True if empty, false otherwise
   // Functions called: None
   bool isEmpty() const;
};

//--------------------------------------------------------------------------
// LinkedList();
// Constructor for a LinkedList
// Preconditions: Memory available
// Postconditions: New LinkedList with head & tail set to nullptr
// Return value: None
// Functions called: None
template <typename Data>
LinkedList<Data>::LinkedList() {
   head = nullptr;
   tail = nullptr;
}

//--------------------------------------------------------------------------
// ~LinkedList();
// Destructor for LinkedList. 
// Preconditions: LinkedList
// Postconditions: LinkedList destructed with no memory leaks
// Return value: None
// Functions called: None
template <typename Data>
LinkedList<Data>::~LinkedList() {
   if (isEmpty()) { return; }
   Node* nextNode = head;
   Node* current = nullptr;
   while (nextNode != nullptr) {
      current = nextNode;
      nextNode = nextNode->next;
      delete current->data;
      delete current;
   }
   head = nullptr;
}

//--------------------------------------------------------------------------
// bool addLast(Data*)
// Preconditions: Data* exists
// Postconditions: LinkedList exists and has at least one Node with type
// Data of toAdd, where toAdd is last in the LinkedList.
// Return value: bool: true if added, false otherwise
// Functions called: newNode
template <typename Data>
void LinkedList<Data>::addLast(Data* newData) {
   if (isEmpty()) {
      Node* toAdd = newNode(newData);
      head = toAdd;
      tail = toAdd;
   }
   else {
      Node* toAdd = newNode(newData);
      tail->next = toAdd;
      tail = tail->next;
   }
}

//--------------------------------------------------------------------------
// bool addLastNode(Node* toAdd);
// Preconditions: Node* exists
// Postconditions: LinkedList exists and has at least one Node with type
// Data of toAdd, where toAdd is last in the LinkedList.
// Return value: bool: true if added, false otherwise
// Functions called: newNode
template <typename Data>
void LinkedList<Data>::addLastNode(Node* toAdd) {
   if (isEmpty()) {
      head = toAdd;
      tail = toAdd;
   }
   else {
      tail->next = toAdd;
      tail = tail->next;
   }
}

//--------------------------------------------------------------------------
// Node* removeFirst();
// Preconditions: LinkedList with at least one Node exists
// Postconditions: LinkedList with the first node removed
// Return value: Node*
// Functions called: None
template <typename Data>
typename LinkedList<Data>::Node* LinkedList<Data>::removeFirst() {
   if (isEmpty()) { return nullptr; }
   Node* toReturn = head;
   if (head == tail) {
      head = nullptr;
      tail = nullptr;
   }
   else {
      head = head->next;
   }
   toReturn->next = nullptr;
   return toReturn;
}

//--------------------------------------------------------------------------
// Data* getData(Node* aNode)
// Preconditions: LinkedList exists with a Node. 
// Postconditions: No change to LinkedList
// Return value: Data value from within a Node
// Functions called: None.
template <typename Data>
Data* LinkedList<Data>::getData(Node* aNode) {
   return aNode->data;
}

//--------------------------------------------------------------------------
// bool isEmpty() const;
// Preconditions: LinkedList exists
// Postconditions: LinkedList is unchanged
// Return value: True if empty, false otherwise
// Functions called: None
template <typename Data>
bool LinkedList<Data>::isEmpty() const {
   return head == nullptr;
}

//--------------------------------------------------------------------------
// Node* newNode(Data* newData)
// Creates a new Node with Data type
// Preconditions: Data is valid
// Postconditions: new Node created with type Data
// Return value: Node* 
// Functions called: None
template <typename Data>
typename LinkedList<Data>::Node* LinkedList<Data>::newNode(Data* newData) {
   try {
      Node* toAdd = new Node;
      toAdd->data = newData;
      toAdd->next = nullptr;
      return toAdd;
   }
   catch (...) {
      cout << "You are out of memory.\n";
      exit(0);
   }
}

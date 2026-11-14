/***********************************************************
 ** File:    LList.h
 ** Project: CMSC 202 - Project 5
 ** This file contains the details about the container (both FIFO and LIFO)
 **********************************************************/
#ifndef LLIST_H
#define LLIST_H

#include <iostream>
using namespace std;

// Templated singly linked list that supports both queue and stack operations
template <class T>
class LList {
public:
	// Name - LList (Constructor)
	// Desc - Initializes an empty linked list with no nodes.
	// Preconditions  - None
	// Postconditions - m_head and m_tail are nullptr; m_size is 0
	LList();

	// Name - LList (Copy Constructor)
	// Desc - Creates a deep copy of another LList, duplicating all nodes in order.
	// Preconditions  - source must be a valid LList instance
	// Postconditions - A new list with identical elements is created
	//        (in different memory location)
	LList(const LList<T>& source);

	// Name - operator= (Assignment Operator)
	// Desc - Deep copies another LList into this one, replacing existing contents.
	//        Handles self-assignment safely.
	  // Preconditions  - source must be a valid LList instance
  // Postconditions - This list contains a deep copy of other's elements;
  //                  previous nodes are freed; returns *this
	LList<T>& operator=(const LList<T>& source);

	// Name - ~LList (Destructor)
	// Desc - Deallocates all nodes in the list
	// Preconditions  - None
	// Postconditions - All dynamically allocated nodes are freed; list is empty
	~LList();

	// Name - Enqueue
	// Desc - Inserts a new node containing data at the back of the list.
	//        Used to model queue (FIFO) behavior. Uses m_tail to insert.
	// Preconditions  - None
	// Postconditions - A new node is appended at the tail; m_size is incremented by 1
	void Enqueue(T data);

	// Name - Dequeue
	// Desc - Removes and returns the data from the front node of the list.
	//        Used to model queue (FIFO) behavior.
	//        Prints an error and returns a default-constructed
	//        T if the list is empty. (return T{})
	// Preconditions  - List should be non-empty before calling
	// Postconditions - Front node is deleted; m_head advances;
	//        m_size is decremented by 1
	T Dequeue();

	// Name - Push
	// Desc - Inserts a new node containing data at the front of the list.
	//        Used to model stack (LIFO) behavior.
	// Preconditions  - None
	  // Postconditions - A new node is prepended at the head;
  //        m_size is incremented by 1
	void Push(T data);

	// Name - Pop
	// Desc - Removes and returns the data from the front node of the list.
	//        Used to model stack (LIFO) behavior. Calls Dequeue internally.
	//        Prints an error and returns a default-constructed
	//        T if the list is empty. (return T{})
	// Preconditions  - List must be non-empty
	// Postconditions - Front node is deleted; m_head advances;
	//        m_size is decremented by 1
	T Pop();

	// Name - Peek
	// Desc - Returns the data at the front of the list without removing the node.
	  //        Prints an error and returns a default-constructed
  //        T if the list is empty. (return T{})
  // Preconditions  - List must be non-empty
  // Postconditions - List is unchanged; front element's data is returned
	T Peek() const;

	// Name - IsEmpty
	// Desc - Returns true if the list contains no nodes, false otherwise.
	// Preconditions  - None
	// Postconditions - List is unchanged
	bool IsEmpty() const;

	// Name - Size
	// Desc - Returns the current number of nodes in the list.
	// Preconditions  - None
	// Postconditions - List is unchanged; m_size is returned
	int Size() const;

	// Name - Display
	// Desc - Traverses the list from head to tail and prints each element
	//        using its overloaded operator<<.
	// Preconditions  - T must have an overloaded operator<<
	// Postconditions - All elements are printed to cout; list is unchanged
	void Display() const;

	// Name - GetAt
	// Desc - Returns the data of the node at the given 0-based index
	//        without removing it. Traverses from the head each call.
	//        Prints an error and returns a default-constructed
	//        T if the list is empty. (return T{})
	// Preconditions  - index must be >= 0 and < m_size
	// Postconditions - List is unchanged; data at the given index is returned
	T GetAt(int index) const;

	// Name - RemoveAt
	// Desc - Removes and returns the element at the given zero-based index.
	//        Supports removing a selected inventory item (not just head/tail).
	// Preconditions - index must be between 0 and m_size - 1
	// Postconditions - Selected node is deleted and links, tail, and size updated.
	//                  Invalid indexes print an error and return T{}.
	T RemoveAt(int index);

	// Name - Clear
	// Desc - Removes and deallocates all nodes in the list by repeatedly
	//        calling Dequeue until the list is empty.
	// Preconditions  - None
	// Postconditions - All nodes are freed; m_head and m_tail are nullptr;
	//        m_size is 0
	void Clear();

private:
	struct Node {
		T m_data; //Data for template
		Node* m_next; //Node pointer to next node
		Node(T data) : m_data(data), m_next(nullptr) {} //Overloaded constructor
	};

	Node* m_head; //Node pointer to first node in list
	Node* m_tail; //Node pointer to last node in list
	int m_size; //Number of nodes in list
};

// ---- Implementation ----
// Template implementations must live in this header file


#endif
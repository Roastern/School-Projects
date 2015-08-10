/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Assignment 4
* Filename:			doublelinkedlist.h
* Date Created:		4/22/2014
* Modifications:	
*
************************************************************/

#ifndef DOUBLELNKDLIST_H_
#define DOUBLELNKDLIST_H_

#include <iostream>
#include "node.h"
using std::cout;
using std::endl;

/************************************************************************
* Class: DoubleLinkedList
*
* Purpose: This class creates a double linked list of Node objects
*
* Manager functions:	
* 	DoubleLinkedList ( )
* 		head and tail are set to nullptr 	
*	DoubleLinkedList (const DoubleLinkedList<T> & copy)
*		A copy of the linked list stored in copy is made and stored in
*		the new DoubleLinkedList object
*	DoubleLinkedList<T> & operator=(const DoubleLinkedList<T> & copy)
*		The linked list in the current object is deleted and the list in
*		copy is copied, and then stored in the current object
*	~DoubleLinkedList ( )
*		Calls Purge() to delete the dynamically allocated list
*
* Methods:		
*
*	getHead ( )
*		Returns a pointer to head
*	getTail ( )
*		Returns a pointer to tail
*	setHead (const T nData)
*		Stores nData in head
*	setTail (const T nData)
*		Stores nData in tail
*	isEmpty ( )
*		Determines wether the linked list is empty
*	First ( )
*		Returns a reference to head
*	Last ( )
*		Returns a reference to tail
*	Prepend (const T nData)
*		Creates a new node with the value of nData and places it
*		at the beginning of the list
*	Append (const T nData)
*		Creates a new node with the value of nData and places it
*		at the end of the list
*	Purge ( )
*		Deletes all the Nodes stored in list
*	Extract (const T data)
*		Deletes a Node within list which has the value nData
*		stored in it
*	InsertAfter (const T nData, const T pos)
*		Creates a new Node and stores nData in it, then places the new
*		Node after a node with the value pos stored in it
*	InsertBefore (const T nData, const T pos)
*		Creates a new Node and stores nData in it, then places the new
*		Node before a Node with the value pos stored in it
*	PrintForwards ( )
*		Prints the list from front to back
*	PrintBackwards ( )
*		Prints the list from back to front
*	FindNode (const T nData)
*		Finds the first Node in the list with the value nData stored
*		in it
*************************************************************************/
template<typename T>
class DoubleLinkedList
{
public:
	DoubleLinkedList();
	DoubleLinkedList(const DoubleLinkedList<T> & copy);
	DoubleLinkedList<T> & operator=(const DoubleLinkedList<T> & copy);
	~DoubleLinkedList();

	const Node<T> * getHead() const;
	const Node<T> * getTail() const;
	void setHead(const T nData);
	void setTail(const T nData);

	bool isEmpty() const;

	const Node<T> & First() const;
	const Node<T> & Last() const;

	void Prepend(const T nData);
	void Append(const T nData);

	void Purge();
	void Extract(const T data);

	void InsertAfter(const T nData, const T pos);
	void InsertBefore(const T nData, const T pos);

	void PrintForwards() const;
	void PrintBackwards() const;

private:
	Node<T> * FindNode(const T nData);
	Node<T> * head;
	Node<T> * tail;
};

/**********************************************************************	
* Purpose: Default constructor, sets head and tail to nullptr
*
* Entry: No values are entered
*
* Exit: head and tail are set to nullptr
*
************************************************************************/
template<typename T>
DoubleLinkedList<T>::DoubleLinkedList() : head(nullptr), tail(nullptr)
{

}

/**********************************************************************	
* Purpose: The linked list stored in copy is copied and stored in
*			the new DoubleLinkedList object
*
* Entry: copy is the DoubleLinkedList object to be copied
*
* Exit: head points to the start of the copied list, tail to the end
*
************************************************************************/
template<typename T>
DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList<T> & copy)
{
	if (!copy.isEmpty())
	{
		head = new Node<T>(copy.head->data);
		Node<T> * newNode;
		Node<T> * curr = head;
		const Node<T> * source = copy.head->next;

		while(source)
		{
			newNode = new Node<T>(source->data);
			newNode->setPrevious(curr);
			curr->setNext(newNode);
			curr = newNode;
			source = source->next;
		}

		tail = curr;
	}
	else
	{
		head = nullptr;
		tail = nullptr;
	}
}

/**********************************************************************	
* Purpose: Clears the list in the current object, then copied the list
*			stored in copy into it
*
* Entry: copy is the DoubleLinkedList object to be copied
*
* Exit: head points to the start of the copy of the list, tail to the end
*
************************************************************************/
template<typename T>
DoubleLinkedList<T> & DoubleLinkedList<T>::operator=(const DoubleLinkedList<T> & copy)
{
	Purge();

	if (!copy.isEmpty())
	{
		head = new Node<T>(copy.head->data);
		Node<T> * newNode;
		Node<T> * curr = head;
		const Node<T> * source = copy.head->next;

		while(source)
		{
			newNode = new Node<T>(source->data);
			newNode->setPrevious(curr);
			curr->setNext(newNode);
			curr = newNode;
			source = source->next;
		}

		tail = curr;
	}

	return *this;
}

/**********************************************************************	
* Purpose: Destroys the DoubleLinkedList object
*
* Entry: No values are entered
*
* Exit: Calls Purge() to destroy the list
*		Nothing is returned
*
************************************************************************/
template<typename T>
DoubleLinkedList<T>::~DoubleLinkedList()
{
	Purge();
}

/**********************************************************************	
* Purpose: Returns a pointer to the head of the list
*
* Entry: No values are entered
*
* Exit: A pointer to head is returned
*
************************************************************************/
template<typename T>
const Node<T> * DoubleLinkedList<T>::getHead() const
{
	return head;
}

/**********************************************************************	
* Purpose: Returns a pointer to the end of the list
*
* Entry: No values are entered
*
* Exit: A pointer to tail is returned
*
************************************************************************/
template<typename T>
const Node<T> * DoubleLinkedList<T>::getTail() const
{
	return tail;
}

/**********************************************************************	
* Purpose: Creates a new Node with the given data, then places it at
*			the head of the list
*
* Entry: nData is the data which will be stored at the head of the list
*
* Exit: nNode is created and nData is stored within
*		nNode is placed at the head of the list
*
************************************************************************/
template<typename T>
void DoubleLinkedList<T>::setHead(const T nData)
{
	Node<T> * nNode = new Node<T>(nData)

	if (head != nullptr)
	{
		nNode->setNext(head);
		head = nNode;
	}
	else
	{
		head = nNode;
		tail = nNode;
	}
}

/**********************************************************************	
* Purpose: Creates a new Node with the given data, then places it at
*			the tail of the list
*
* Entry: nData is the data which will be stored at the tail of the list
*
* Exit: nNode is created and nData is stored within
*		nNode is placed at the tail of the list
*
************************************************************************/
template<typename T>
void DoubleLinkedList<T>::setTail(const T nData)
{
	Node<T> * nNode = new Node<T>(nData);

	if (head == nullptr)
	{
		head = nNode;
		tail = nNode;
	}
	else
	{
		nNode->setPrevious(tail);
		tail = nNode;
	}
}

/**********************************************************************	
* Purpose: Determines whether the list is empty
*
* Entry: No values are passed to this function
*
* Exit: Returns true if the list is empty, false if not
*
************************************************************************/
template<typename T>
bool DoubleLinkedList<T>::isEmpty() const
{
	bool empty;

	if (head == nullptr)
		empty = true;
	else 
		empty = false;

	return empty;
}

/**********************************************************************	
* Purpose: Returns a reference to the head of the list
*
* Entry: No values are passed into this function
*
* Exit: A reference to head is returned
*
************************************************************************/
template<typename T>
const Node<T> & DoubleLinkedList<T>::First() const
{
	return *head;
}

/**********************************************************************	
* Purpose: Returns a reference to the tail of the list
*
* Entry: No values are passed into this function
*
* Exit: A reference to tail is returned
*
************************************************************************/
template<typename T>
const Node<T> & DoubleLinkedList<T>::Last() const
{
	return *tail;
}

/**********************************************************************	
* Purpose: Creates a new node with the given data and places it at the
*			beginning of the list
*
* Entry: nData is the data to be stored in the new Node
*
* Exit: head is set to the new node
*		No values are returned
*
************************************************************************/
template<typename T>
void DoubleLinkedList<T>::Prepend(const T nData)
{
	Node<T> * nNode = new Node<T>(nData);

	if (head != nullptr)
	{
		nNode->setNext(head);
		head->setPrevious(nNode);
		head = nNode;
	}
	else
	{
		head = nNode;
		tail = nNode;
	}
}

/**********************************************************************	
* Purpose: Creates a new node with the given data and places it at the
*			end of the list
*
* Entry: nData is the data to be stored in the new Node
*
* Exit: tail is set to the new node
*		No values are returned
*
************************************************************************/
template<typename T>
void DoubleLinkedList<T>::Append(const T nData)
{
	Node<T> * nNode = new Node<T>(nData);

	if (head == nullptr)
	{
		head = nNode;
		tail = nNode;
	}
	else if (tail != nullptr)
	{
		nNode->setPrevious(tail);
		tail->setNext(nNode);
		tail = nNode;
	}
	else
	{
		tail = nNode;
	}
}

/**********************************************************************	
* Purpose: Deletes all the Nodes stored in the list
*
* Entry: No values are passed to this function
*
* Exit: No values are returned
*		The list is deleted
*
************************************************************************/
template<typename T>
void DoubleLinkedList<T>::Purge()
{
	Node<T> * curr = head;
	Node<T> * prev = head;

	while (curr != nullptr)
	{
		curr = curr->next;
		delete prev;
		prev = curr;
	}

	head = nullptr;
	tail = nullptr;
	curr = nullptr;
	prev = nullptr;
}

/**********************************************************************	
* Purpose: Deletes a given Node from the list
*
* Entry: nData is the data to be removed from the list
*
* Exit: If the given data is found within the list, it is deleted
*		No values are returned
*
************************************************************************/
template<typename T>
void DoubleLinkedList<T>::Extract(const T nData)
{
	Node<T> * curr = FindNode(nData);
	char error[] = "Data was not found in list";

	if (curr == nullptr)
	{
		throw error;
	}

	if (head == curr)
	{
		head = head->next;
		if (tail == curr)
			tail = head;
		if (head)
			head->setPrevious(nullptr);
		delete curr;
	}
	else if (tail == curr)
	{
		tail = tail->previous;
		if (tail)
			tail->setNext(nullptr);
		delete curr;
	}
	else
	{
		Node<T> * prev = curr->previous;
		prev->setNext(curr->next);
		prev = prev->next;
		prev->setPrevious(curr->previous);
		delete curr;
	}
}

/**********************************************************************	
* Purpose: Creates and inserts a new Node with the given data and places
*			it after the specified Node
*
* Entry: nData is the data to be stored in the new Node
*		 pos is the data of the Node where the new Node should be placed
*			after
*
* Exit: If the given position is found, places the new Node after the
*			given position
*
************************************************************************/
template<typename T>
void DoubleLinkedList<T>::InsertAfter(const T nData, const T pos)
{
	Node<T> * curr = FindNode(pos);
	char error[] = "Cannot insert data";

	if (curr == nullptr)
	{
		throw error;
	}

	Node<T> * nNode = new Node<T>(nData);

	if (tail == curr)
	{
		tail = nNode;
		nNode->setPrevious(curr);
		curr->setNext(tail);
	}
	else
	{
		Node<T> * prev = curr;
		curr = curr->next;

		prev->setNext(nNode);
		curr->setPrevious(nNode);
		nNode->setNext(curr);
		nNode->setPrevious(prev);
	}

}

/**********************************************************************	
* Purpose: Creates and inserts a new Node with the given data and places
*			it before the specified Node
*
* Entry: nData is the data to be stored in the new Node
*		 pos is the data of the Node where the new Node should be placed
*			before
*
* Exit: If the given position is found, places the new Node before the
*			given position
*
************************************************************************/
template<typename T>
void DoubleLinkedList<T>::InsertBefore(const T nData, const T pos)
{
	Node<T> * curr = FindNode(pos);
	char error[] = "Cannot insert data";

	if (curr == nullptr)
	{
		throw error;
	}

	Node<T> * nNode = new Node<T>(nData);

	if (head == curr)
	{
		head = nNode;
		head->setNext(curr);
		curr->setPrevious(head);
	}
	else
	{
		Node<T> * prev = curr->previous;

		prev->setNext(nNode);
		curr->setPrevious(nNode);
		nNode->setPrevious(prev);
		nNode->setNext(curr);
	}
}

/**********************************************************************	
* Purpose: Prints the list from head to tail
*
* Entry: No values are passed into this function
*
* Exit: No values are returned
*
************************************************************************/
template<typename T>
void DoubleLinkedList<T>::PrintForwards() const
{
	Node<T> * curr = head;

	cout << endl;

	while (curr != nullptr)
	{
		cout << *curr << endl;
		curr = curr->next;
	}
}

/**********************************************************************	
* Purpose: Prints the list from tail to head
*
* Entry: No values are passed into this function
*
* Exit: No values are returned
*
************************************************************************/
template<typename T>
void DoubleLinkedList<T>::PrintBackwards() const
{
	Node<T> * curr = tail;

	cout << endl;

	while (curr != nullptr)
	{
		cout << *curr << endl;
		curr = curr->previous;
	}
}

/**********************************************************************	
* Purpose: Finds a Node within the list which has the given data stored
*			in it, then returns a pointer to that node
*
* Entry: nData is the data which is being searched for
*
* Exit: A pointer to the Node is returned if found
*		if no Node with the given data is found, nullptr is returned
*
************************************************************************/
template<typename T>
Node<T> * DoubleLinkedList<T>::FindNode(const T nData)
{
	bool found = false;
	Node<T> * curr = head;

	while (curr != nullptr && !found)
	{
		if (curr->getData() == nData)
		{
			found = true;
		}
		else
			curr = curr->next;
	}

	return curr;
}
#endif
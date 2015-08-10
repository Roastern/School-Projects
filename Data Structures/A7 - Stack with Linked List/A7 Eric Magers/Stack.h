/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Assignment 7
* Filename:			Stack.h
* Date Created:		4/23/2014
* Modifications:	
*
************************************************************/

#ifndef LLSTACK_H_
#define LLSTACK_H_

#include "doublelinkedlist.h"
#include "Exception.h"


/************************************************************************
* Class: Stack
*
* Purpose: This class creates a dynamic a stack implemented with a double
*			linked list
*
* Manager functions:	
* 	Stack ( )
* 		Creates a stack 	
*	Stack (const Stack & copy)
*		Creates an a stack same data stored in it as copy
*	operator = (const Stack & copy)
*		Copies the size and data from copy into the current Stack
*	~Stack()
*		deletes the Stack
*
* Methods:		
*	Push (T nData)
*		Places an element onto the Stack
*	Peek ( ) const
*		Returns a constant reference to the element at the top of the Stack
*	Pop ( )
*		Returns the element at the top of the stack, deletes that element
*	Size ( ) const
*		Returns the size of the stack
*	isEmpty ( ) const
*		Returns true if the stack is empty
*		
*************************************************************************/
template<typename T>
class Stack
{
public:
	Stack();
	Stack(const Stack<T> & copy);
	Stack<T> & operator=(const Stack<T> & copy);
	~Stack();

	void Push(T nData);
	const T& Peek() const;
	T Pop();
	int Size() const;
	bool isEmpty() const;

private:
	DoubleLinkedList<T> m_list;
	int curr_size;
};

/**********************************************************************	
* Purpose: Default constructor, initializes the stack 
*
* Entry: No values are passed to this function
*
* Exit: A Stack object is created
*
************************************************************************/
template<typename T>
Stack<T>::Stack() : m_list(), curr_size(0)
{

}

/**********************************************************************	
* Purpose: A copy of the given stack is made and stored in the new stack
*
* Entry: copy is the stack to be copied
*
* Exit: copy's m_list is copied into list, curr_size is set to 
*		copy's curr_size
*
************************************************************************/
template<typename T>
Stack<T>::Stack(const Stack<T> & copy) : m_list(copy.m_list), curr_size(copy.curr_size)
{

}

/**********************************************************************	
* Purpose: A copy of the given stack is made and stored in the given
*			stack
*
* Entry: copy is the stack to be copied
*
* Exit: copy's m_list is copied into m_list, curr_size is set to 
*		copy's curr_size
*
************************************************************************/
template<typename T>
Stack<T> & Stack<T>::operator=(const Stack<T> & copy)
{
	m_list = copy.m_list;
	curr_size = copy.Size();

	return *this;
}

/**********************************************************************	
* Purpose: Destroys the stack object
*
* Entry: No values are passed to this function
*
* Exit: No values are returned
*
************************************************************************/
template<typename T>
Stack<T>::~Stack()
{

}

/**********************************************************************	
* Purpose: The given data is placed on the top of the stack
*
* Entry: nData is the data to be placed on the stack
*
* Exit: nData is placed on the top of the stack
*		Nothing is returned
*
************************************************************************/
template<typename T>
void Stack<T>::Push(T nData)
{
	m_list.Append(nData);
	curr_size++;
}

/**********************************************************************	
* Purpose: Returns a reference to the data at the top of the stack
*
* Entry: No variables are passed to this function
*
* Exit: A constant reference to the data stored at the element at the
*		top of the stack is returned
*
************************************************************************/
template<typename T>
const T& Stack<T>::Peek() const
{
	if (isEmpty())
	{
		throw Exception("Stack is empty");
	}

	return m_list.Last().getData();
}

/**********************************************************************	
* Purpose: Removes the data stored in the top of the stack
*
* Entry: No variables are passed to this function
*
* Exit: A copy of the data at the top of the stack is made
*		The element at the top of the stack is deleted
*		The copy of the data is returned
*
************************************************************************/
template<typename T>
T Stack<T>::Pop()
{
	if (isEmpty())
	{
		throw Exception("Stack is empty");
	}

	T ret = m_list.Last().getData();
	m_list.Extract(ret);
	curr_size--;

	return ret;
}

/**********************************************************************	
* Purpose: Returns the current size of the stack
*
* Entry: No variables are passed to this function
*
* Exit: curr_size is returned
*
************************************************************************/
template<typename T>
int Stack<T>::Size() const 
{
	return curr_size;
}

/**********************************************************************	
* Purpose: Determines whether or not the stack is empty
*
* Entry: No variables are passed to this function
*
* Exit: Returns true if the stack is empty
*		Returns false if the stack has data in it
*
************************************************************************/
template<typename T>
bool Stack<T>::isEmpty() const
{
	bool empty = false;

	if (curr_size == 0)
		empty = true;

	return empty;
}

#endif
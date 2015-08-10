/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Assignment 6
* Filename:			Stack.h
* Date Created:		4/22/2014
* Modifications:	
*
************************************************************/
#include "Array.h"

/************************************************************************
* Class: Stack
*
* Purpose: This class creates a dynamic a stack implemented with an Array
*			object
*
* Manager functions:	
* 	Stack (int size )
* 		Creates a stack of the given size  	
*	Stack (const Stack & copy)
*		Creates an a stack of the same size and with the same data stored in
*			it as copy
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
*	isFull ( ) const
*		Returns true if the stack is full
*		
*************************************************************************/
template<typename T>
class Stack
{
public:
	Stack(int size);
	Stack(const Stack & copy);
	Stack<T> & operator=(const Stack & copy);
	~Stack();

	void Push(T nData);
	const T& Peek() const;
	T Pop();
	int Size() const;
	bool isEmpty() const;
	bool isFull() const;

private:
	Array<T> m_array;
	int curr_size;
};

/**********************************************************************	
* Purpose: Default constructor, initializes the stack to be of the given
*			size
*
* Entry: size is the size m_array is set to
*
* Exit: m_array is set to the length size and curr_size is set to 0
*
************************************************************************/
template<typename T>
Stack<T>::Stack(int size) : m_array(size), curr_size(0)
{

}

/**********************************************************************	
* Purpose: A copy of the given stack is made and stored in the new stack
*
* Entry: copy is the stack to be copied
*
* Exit: copy's m_array is copied into m_array, curr_size is set to 
*		copy's curr_size
*
************************************************************************/
template<typename T>
Stack<T>::Stack(const Stack<T> & copy) : m_array(), curr_size(copy.Size())
{
	m_array = copy.m_array;
}

/**********************************************************************	
* Purpose: A copy of the given stack is made and stored in the given
*			stack
*
* Entry: copy is the stack to be copied
*
* Exit: copy's m_array is copied into m_array, curr_size is set to 
*		copy's curr_size
*
************************************************************************/
template<typename T>
Stack<T> & Stack<T>::operator=(const Stack & copy)
{
	m_array = copy.m_array;
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
	if (isFull())
	{
		throw Exception("Cannot place any new objects on the stack");
	}

	m_array[curr_size] = nData;
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
	if(isEmpty())
	{
		throw Exception("No items are on the stack");
	}

	return m_array[curr_size - 1];
}

/**********************************************************************	
* Purpose: Removes the data stored in the element at the top of the stack
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
	if(isEmpty())
	{
		throw Exception("No items are on the stack");
	}

	curr_size--;
	T ret = m_array[curr_size];
	m_array[curr_size] = T();
	
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

/**********************************************************************	
* Purpose: Determines whether or not the stack is full
*
* Entry: No variables are passed to this function
*
* Exit: Returns true if the stack is full
*		Returns false if curr_size is less than m_array.getLength()
*
************************************************************************/
template<typename T>
bool Stack<T>::isFull() const
{
	bool full = false;

	if (curr_size == m_array.getLength())
		full = true;

	return full;
}
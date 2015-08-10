/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Assignment 7
* Filename:			LStack.h
* Date Created:		4/23/2014
* Modifications:	
*
************************************************************/

#ifndef LStack_H_
#define LStack_H_

#include "doublelinkedlist.h"
#include "Exception.h"


/************************************************************************
* Class: LStack
*
* Purpose: This class creates a dynamic a LStack implemented with a double
*			linked list
*
* Manager functions:	
* 	LStack ( )
* 		Creates a LStack 	
*	LStack (const LStack & copy)
*		Creates an a LStack same data stored in it as copy
*	operator = (const LStack & copy)
*		Copies the size and data from copy into the current LStack
*	~LStack()
*		deletes the LStack
*
* Methods:		
*	Push (T nData)
*		Places an element onto the LStack
*	Peek ( ) const
*		Returns a constant reference to the element at the top of the LStack
*	Pop ( )
*		Returns the element at the top of the LStack, deletes that element
*	Size ( ) const
*		Returns the size of the LStack
*	isEmpty ( ) const
*		Returns true if the LStack is empty
*		
*************************************************************************/
template<typename T>
class LStack
{
public:
	LStack();
	LStack(const LStack<T> & copy);
	LStack<T> & operator=(const LStack<T> & copy);
	~LStack();

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
* Purpose: Default constructor, initializes the LStack 
*
* Entry: No values are passed to this function
*
* Exit: A LStack object is created
*
************************************************************************/
template<typename T>
LStack<T>::LStack() : m_list(), curr_size(0)
{

}

/**********************************************************************	
* Purpose: A copy of the given LStack is made and stored in the new LStack
*
* Entry: copy is the LStack to be copied
*
* Exit: copy's m_list is copied into list, curr_size is set to 
*		copy's curr_size
*
************************************************************************/
template<typename T>
LStack<T>::LStack(const LStack<T> & copy) : m_list(copy.m_list), curr_size(copy.curr_size)
{

}

/**********************************************************************	
* Purpose: A copy of the given LStack is made and stored in the given
*			LStack
*
* Entry: copy is the LStack to be copied
*
* Exit: copy's m_list is copied into m_list, curr_size is set to 
*		copy's curr_size
*
************************************************************************/
template<typename T>
LStack<T> & LStack<T>::operator=(const LStack<T> & copy)
{
	m_list = copy.m_list;
	curr_size = copy.Size();

	return *this;
}

/**********************************************************************	
* Purpose: Destroys the LStack object
*
* Entry: No values are passed to this function
*
* Exit: No values are returned
*
************************************************************************/
template<typename T>
LStack<T>::~LStack()
{

}

/**********************************************************************	
* Purpose: The given data is placed on the top of the LStack
*
* Entry: nData is the data to be placed on the LStack
*
* Exit: nData is placed on the top of the LStack
*		Nothing is returned
*
************************************************************************/
template<typename T>
void LStack<T>::Push(T nData)
{
	m_list.Append(nData);
	curr_size++;
}

/**********************************************************************	
* Purpose: Returns a reference to the data at the top of the LStack
*
* Entry: No variables are passed to this function
*
* Exit: A constant reference to the data stored at the element at the
*		top of the LStack is returned
*
************************************************************************/
template<typename T>
const T& LStack<T>::Peek() const
{
	if (isEmpty())
	{
		throw Exception("LStack is empty");
	}

	return m_list.Last().getData();
}

/**********************************************************************	
* Purpose: Removes the data stored in the top of the LStack
*
* Entry: No variables are passed to this function
*
* Exit: A copy of the data at the top of the LStack is made
*		The element at the top of the LStack is deleted
*		The copy of the data is returned
*
************************************************************************/
template<typename T>
T LStack<T>::Pop()
{
	if (isEmpty())
	{
		throw Exception("LStack is empty");
	}

	T ret = m_list.Last().getData();
	m_list.Extract(ret);
	curr_size--;

	return ret;
}

/**********************************************************************	
* Purpose: Returns the current size of the LStack
*
* Entry: No variables are passed to this function
*
* Exit: curr_size is returned
*
************************************************************************/
template<typename T>
int LStack<T>::Size() const 
{
	return curr_size;
}

/**********************************************************************	
* Purpose: Determines whether or not the LStack is empty
*
* Entry: No variables are passed to this function
*
* Exit: Returns true if the LStack is empty
*		Returns false if the LStack has data in it
*
************************************************************************/
template<typename T>
bool LStack<T>::isEmpty() const
{
	bool empty = false;

	if (curr_size == 0)
		empty = true;

	return empty;
}

#endif
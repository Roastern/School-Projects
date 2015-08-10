/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Assignment 6
* Filename:			AAStack.h
* Date Created:		4/22/2014
* Modifications:	4/27/2014 - Changed Stack to AStack to 
*					specify that it is an array based AAStack
*					4/29/2014 - Added a default constructor 
*								AStack()
*
************************************************************/
#ifndef ASTACK_H_
#define ASTACK_H_

#include "Array.h"

/************************************************************************
* Class: AStack
*
* Purpose: This class creates a dynamic a AStack implemented with an Array
*			object
*
* Manager functions:	
*	AStack ( ) 
*		Creates an AStack of a default size
* 	AStack (int size )
* 		Creates a AStack of the given size  	
*	AStack (const AAStack & copy)
*		Creates an a AStack of the same size and with the same data stored in
*			it as copy
*	operator = (const AStack & copy)
*		Copies the size and data from copy into the current AStack
*	~AStack()
*		deletes the AStack
*
* Methods:		
*	Push (T nData)
*		Places an element onto the AStack
*	Peek ( ) const
*		Returns a constant reference to the element at the top of the AStack
*	Pop ( )
*		Returns the element at the top of the AStack, deletes that element
*	Size ( ) const
*		Returns the size of the AStack
*	isEmpty ( ) const
*		Returns true if the AStack is empty
*	isFull ( ) const
*		Returns true if the AStack is full
*		
*************************************************************************/
const int DEFAULT_SIZE = 13;

template<typename T>
class AStack
{
public:
	AStack();
	AStack(int size);
	AStack(const AStack & copy);
	AStack<T> & operator=(const AStack & copy);
	~AStack();

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
* Purpose: Default constructor, initializes the AStack to be of the size
*			
*
* Entry: size is the size m_array is set to
*
* Exit: m_array is set to the length size and curr_size is set to 0
*
************************************************************************/
template<typename T>
AStack<T>::AStack() : m_array(DEFAULT_SIZE), curr_size(0)
{

}

/**********************************************************************	
* Purpose: initializes the AStack to be of the given size
*
* Entry: size is the size m_array is set to
*
* Exit: m_array is set to the length size and curr_size is set to 0
*
************************************************************************/
template<typename T>
AStack<T>::AStack(int size) : m_array(size), curr_size(0)
{

}

/**********************************************************************	
* Purpose: A copy of the given AStack is made and stored in the new AStack
*
* Entry: copy is the AStack to be copied
*
* Exit: copy's m_array is copied into m_array, curr_size is set to 
*		copy's curr_size
*
************************************************************************/
template<typename T>
AStack<T>::AStack(const AStack<T> & copy) : m_array(), curr_size(copy.Size())
{
	m_array = copy.m_array;
}

/**********************************************************************	
* Purpose: A copy of the given AStack is made and stored in the given
*			AStack
*
* Entry: copy is the AStack to be copied
*
* Exit: copy's m_array is copied into m_array, curr_size is set to 
*		copy's curr_size
*
************************************************************************/
template<typename T>
AStack<T> & AStack<T>::operator=(const AStack & copy)
{
	m_array = copy.m_array;
	curr_size = copy.Size();

	return *this;
}

/**********************************************************************	
* Purpose: Destroys the AStack object
*
* Entry: No values are passed to this function
*
* Exit: No values are returned
*
************************************************************************/
template<typename T>
AStack<T>::~AStack()
{

}

/**********************************************************************	
* Purpose: The given data is placed on the top of the AStack
*
* Entry: nData is the data to be placed on the AStack
*
* Exit: nData is placed on the top of the AStack
*		Nothing is returned
*
************************************************************************/
template<typename T>
void AStack<T>::Push(T nData)
{
	if (isFull())
	{
		throw Exception("Cannot place any new objects on the AStack");
	}

	m_array[curr_size] = nData;
	curr_size++;
}

/**********************************************************************	
* Purpose: Returns a reference to the data at the top of the AStack
*
* Entry: No variables are passed to this function
*
* Exit: A constant reference to the data stored at the element at the
*		top of the AStack is returned
*
************************************************************************/
template<typename T>
const T& AStack<T>::Peek() const
{
	if(isEmpty())
	{
		throw Exception("No items are on the AStack");
	}

	return m_array[curr_size - 1];
}

/**********************************************************************	
* Purpose: Removes the data stored in the element at the top of the AStack
*
* Entry: No variables are passed to this function
*
* Exit: A copy of the data at the top of the AStack is made
*		The element at the top of the AStack is deleted
*		The copy of the data is returned
*
************************************************************************/
template<typename T>
T AStack<T>::Pop()
{
	if(isEmpty())
	{
		throw Exception("No items are on the AStack");
	}

	curr_size--;
	T ret = m_array[curr_size];
	m_array[curr_size] = T();
	
	return ret;
}

/**********************************************************************	
* Purpose: Returns the current size of the AStack
*
* Entry: No variables are passed to this function
*
* Exit: curr_size is returned
*
************************************************************************/
template<typename T>
int AStack<T>::Size() const
{
	return curr_size;
}

/**********************************************************************	
* Purpose: Determines whether or not the AStack is empty
*
* Entry: No variables are passed to this function
*
* Exit: Returns true if the AStack is empty
*		Returns false if the AStack has data in it
*
************************************************************************/
template<typename T>
bool AStack<T>::isEmpty() const
{
	bool empty = false;

	if (curr_size == 0)
		empty = true;

	return empty;
}

/**********************************************************************	
* Purpose: Determines whether or not the AStack is full
*
* Entry: No variables are passed to this function
*
* Exit: Returns true if the AStack is full
*		Returns false if curr_size is less than m_array.getLength()
*
************************************************************************/
template<typename T>
bool AStack<T>::isFull() const
{
	bool full = false;

	if (curr_size == m_array.getLength())
		full = true;

	return full;
}

#endif
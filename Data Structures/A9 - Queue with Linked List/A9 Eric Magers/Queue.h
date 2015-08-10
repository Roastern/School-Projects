/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Assignment 9
* Filename:			Queue.h
* Date Created:		4/25/2014
* Modifications:	
*
************************************************************/

#ifndef QUEUE_H_
#define QUEUE_H_

#include "doublelinkedlist.h"
#include "Exception.h"

/************************************************************************
* Class: Queue
*
* Purpose: This class creates a Queue based on an Array object
*
* Manager functions:	
* 	Queue ( )
* 		Creates a queue
*	Queue (const Queue & copy)
*		Creates an a Queue with the same data stored in it as copy
*	operator = (const Queue & copy)
*		Copies data from copy into the current Queue
*	~Queue()
*		deletes the Queue
*
* Methods:		
*	Enqueue (T nData)
*		Places an element onto the Queue
*	Front ( ) const
*		Returns a reference to the element at the front of the Queue
*	Dequeue ( )
*		Returns the element at the front of the Queue, deletes that element
*	Size ( ) const
*		Returns the size of the Queue
*	isEmpty ( ) const
*		Returns true if the Queue is empty
*	isFull ( ) const
*		Returns true if the Queue is full
*		
*************************************************************************/
template<typename T>
class Queue
{
public:
	Queue();
	Queue(const Queue<T> & copy);
	Queue<T> & operator=(const Queue<T> & copy);
	~Queue();

	void Enqueue(T nData);
	T Dequeue();
	T& Front() const;
	int Size() const;
	bool isEmpty() const;

private:
	DoubleLinkedList<T> m_list;
	int curr_size;
};

/**********************************************************************	
* Purpose: Default constructor, initializes the Queue
*
* Entry: No values are passed to this function
*
* Exit: A Queue object is created
*
************************************************************************/
template<typename T>
Queue<T>::Queue() : m_list(), curr_size(0)
{

}

/**********************************************************************	
* Purpose: A copy of the given Queue is made and stored in the new Queue
*
* Entry: copy is the Queue to be copied
*
* Exit: copy's m_array is copied into m_array, curr_size is set to 
*		copy's curr_size
*
************************************************************************/
template<typename T>
Queue<T>::Queue(const Queue<T> & copy) : m_list(copy.m_list), curr_size(copy.curr_size)
{

}

/**********************************************************************	
* Purpose: A copy of the given Queue is made and stored in the current Queue
*
* Entry: copy is the Queue to be copied
*
* Exit: copy's m_array is copied into m_array, curr_size is set to 
*		copy's curr_size
*
************************************************************************/
template<typename T>
Queue<T> & Queue<T>::operator=(const Queue<T> & copy)
{
	m_list = copy.m_list;
	curr_size = copy.curr_size;
	
	return *this;
}

/**********************************************************************	
* Purpose: Destroys the queue object
*
* Entry: No values are passed to this function
*
* Exit: No values are returned
*
************************************************************************/
template<typename T>
Queue<T>::~Queue()
{

}

/**********************************************************************	
* Purpose: The given data is placed at the back of the queue
*
* Entry: nData is the data to be placed at the back of the queue
*
* Exit: nData is placed at the back of the queue
*		Nothing is returned
*
************************************************************************/
template<typename T>
void Queue<T>::Enqueue(T nData)
{
	m_list.Append(nData);

	curr_size++;
}

/**********************************************************************	
* Purpose: Removes the data stored at the front of the queue
*
* Entry: No variables are passed to this function
*
* Exit: A copy of the data at the front of the queue is made
*		The element at the front of the queue is deleted
*		The copy of the data is returned
*
************************************************************************/
template<typename T>
T Queue<T>::Dequeue()
{
	if (isEmpty())
	{
		throw Exception("Stack is empty");
	}

	T ret = m_list.First().getData();
	m_list.Extract(ret);

	curr_size--;

	return ret;
}

/**********************************************************************	
* Purpose: Returns a reference to the data at the front of the queue
*
* Entry: No variables are passed to this function
*
* Exit: A reference to the data stored at the front of the queue is returned
*
************************************************************************/
template<typename T>
T& Queue<T>::Front() const
{
	if (isEmpty())
	{
		throw Exception("Stack is empty");
	}

	T& ret = (const_cast<T&>(m_list.First().getData()));

	return ret;
}

/**********************************************************************	
* Purpose: Returns the current size of the queue
*
* Entry: No variables are passed to this function
*
* Exit: curr_size is returned
*
************************************************************************/
template<typename T>
int Queue<T>::Size() const
{
	return curr_size;
}

/**********************************************************************	
* Purpose: Determines whether or not the queue is empty
*
* Entry: No variables are passed to this function
*
* Exit: Returns true if the queue is empty
*		Returns false if the queue has data in it
*
************************************************************************/
template<typename T>
bool Queue<T>::isEmpty() const
{
	bool empty = false;

	if (curr_size == 0)
		empty = true;

	return empty;
}

#endif
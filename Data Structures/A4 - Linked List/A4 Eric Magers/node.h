/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Assignment 4
* Filename:			Node.h
* Date Created:		4/22/2014
* Modifications:	
*
************************************************************/

#ifndef NODE_H_
#define NODE_H
#include <iostream>
using std::ostream;

/************************************************************************
* Class: Node
*
* Purpose: This class creates a Node structure to be used in a linked list
*			which stores a data, next pointer and previous pointer
*
* Manager functions:	
* 	Node ( )
* 		The data is set to the default of it's type, next and previous are
*			set to nullptr.  	
*	Node (T newData)
*		Next and previous are set to nullptr, data is set to newData
*	Node (T newData, Node * nNode, Node * pNode)
*		Next and previous are set to nNode and pNode, respectively,
*		 data is set to newData
*	Node (const Node &copy)
*		next, previous and data are set to the values of their counterparts
*		within copy
*	operator = (const Node &copy)
*		Copies next, previous and data from copy into the current Node object
*	~Node()
*		Deletes the Node
*
* Methods:		
*	operator<<(ostream & out, const Node<T> & nNode)
*		Prints out the data stored in Node to the given ostream
*	getData ( )
*		Returns data
*	getNext ( )
*		Returns a pointer to next
*	getPrevious ( )
*		Returns a pointer to previous
*	setData (T newData)
*		sets data to newData
*	setNext (const Node * nNode)
*		sets next to nNode
*	setPrevious (const Node * pNode)
*		sets previous to pNode
*************************************************************************/

template<typename T>
class DoubleLinkedList;
template<typename T>
class Node;

/**********************************************************************	
* Purpose: Prints the data stored in the Node object to the given 
*			output stream
*
* Entry: out is the output stream to be printed to, nNode is the object
*			whose data will be printed
*
* Exit: data is printed to the out output stream
*
************************************************************************/
template<typename T>
ostream & operator<<(ostream & out, const Node<T> & nNode)
{
	if (!&nNode)
	{
		char error[] = "No data";
		throw error;
	}

	out << nNode.getData();

	return out;
}

template<typename T>
class Node
{ 
	friend class DoubleLinkedList<T>;
	friend ostream & operator<< <>(ostream & out, const Node<T> & nNode);

private:
	Node();
	Node(T newData);
	Node(T newData, Node<T> * nNode, Node<T> * pNode);
	Node(const Node<T> & copy);
	~Node();
	Node<T> & operator=(const Node<T> & copy);

	void setData(T newData);
	void setNext(Node<T> * nNode);
	void setPrevious(Node<T> * pNode);

	Node<T> * next;
	Node<T> * previous;
	T data;

public:
	const T & getData() const;
	const Node<T> * getNext() const;
	const Node<T> * getPrevious() const;
};

/**********************************************************************	
* Purpose: Default constructor, initializes data to it's default value
*			next and previous are set to nullptr
*
* Entry: No values are entered
*
* Exit: All variables within Node are set to their default values
*
************************************************************************/
template<typename T>
Node<T>::Node() : data(), next(nullptr), previous(nullptr)
{

}

/**********************************************************************	
* Purpose: Creates a new Node with a given value for data
*
* Entry: newData is the value to be stored in data
*
* Exit: data is set to newData, next and previous are set to nullptr
*
************************************************************************/
template<typename T>
Node<T>::Node(T newData) : data(newData), next(nullptr), previous(nullptr)
{

}

/**********************************************************************	
* Purpose: Creates a new Node object with values set for data, next
*			and previous
*
* Entry: newData is the value to be stored in data, nNode and pNode
*			are the addresses to be stored in next and previous, 
*			respectively
*
* Exit: All variables within Node are initialized to the given values
*
************************************************************************/
template<typename T>
Node<T>::Node(T newData, Node<T> * nNode, Node<T> * pNode) : data(newData), next(nNode), previous(pNode)
{

}

/**********************************************************************	
* Purpose: Copies the values stored within an existing Node object into
*			a new Node object
*
* Entry: copy is the existing Node object to be copied
*
* Exit: data, next and previous are set to the values of the same variables
*		within copy
*
************************************************************************/
template<typename T>
Node<T>::Node(const Node & copy) : data(copy.getData()), next(copy.getNext()), previous(copy.getPrevious())
{

}

/**********************************************************************	
* Purpose: Destroys the Node object
*
* Entry: No values are entered
*
* Exit: No values are returned
*
************************************************************************/
template<typename T>
Node<T>::~Node()
{
	next = nullptr;
	previous = nullptr;
	data = T();
}

/**********************************************************************	
* Purpose: Copies the values stored in one Node object into another
*
* Entry: copy is the Node object to be copied into the current Node
*
* Exit: data, next, and previous of the current Node object are set to 
*			the corresponding values of the copy object
*
************************************************************************/
template<typename T>
Node<T> & Node<T>::operator=(const Node<T> & copy)
{
	if (*this != *copy)
	{
		data = copy.getData();
		next = copy.getNext();
		previous = copy.getPrevious();
	}
}



/**********************************************************************	
* Purpose: Returns the value stored in data
*
* Entry: No values are entered
*
* Exit: data is returned
*
************************************************************************/
template<typename T>
const T & Node<T>::getData() const
{
	return data;
}

/**********************************************************************	
* Purpose: Returns a pointer to next
*
* Entry: No values are entered
*
* Exit: The pointer to next is returned
*
************************************************************************/
template<typename T>
const Node<T> * Node<T>::getNext() const
{
	return next;
}

/**********************************************************************	
* Purpose: Returns a pointer to previous
*
* Entry: No values are entered
*
* Exit: The pointer to previous is returned
*
************************************************************************/
template<typename T>
const Node<T> * Node<T>::getPrevious() const
{
	return previous;
}

/**********************************************************************	
* Purpose: Stores a value in data
*
* Entry: newData is the value to be stored in data
*
* Exit: newData is stored in data
*
************************************************************************/
template<typename T>
void Node<T>::setData(T newData)
{
	data = newData;
}

/**********************************************************************	
* Purpose: Points next to the given address
*
* Entry: nNode is the pointer to be stored in next
*
* Exit: nNode is stored in next
*
************************************************************************/
template<typename T>
void Node<T>::setNext(Node<T> * nNode)
{
	next = nNode;
}

/**********************************************************************	
* Purpose: Points previous to the given address
*
* Entry: pNode is the address to be stored in previous
*
* Exit: pNode is stored in previous
*
************************************************************************/
template<typename T>
void Node<T>::setPrevious(Node<T> * pNode)
{
	previous = pNode;
}

#endif
/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Assignment 10
* Filename:			BinaryTreeNode.h
* Date Created:		5/10/2014
* Modifications:	
*
************************************************************/

#ifndef BinaryTreeNode_H_
#define BinaryTreeNode_H
#include <iostream>
using std::ostream;

/************************************************************************
* Class: BinaryTreeNode
*
* Purpose: This class creates a BinaryTreeNode structure to be used in a linked list
*			which stores a data, l_child pointer and r_child pointer
*
* Manager functions:	
* 	BinaryTreeNode ( )
* 		The data is set to the default of it's type, l_child and r_child are
*			set to nullptr.  	
*	BinaryTreeNode (T newData)
*		l_child and r_child are set to nullptr, data is set to newData
*	BinaryTreeNode (T newData, BinaryTreeNode * nBinaryTreeNode, BinaryTreeNode * pBinaryTreeNode)
*		l_child and r_child are set to nBinaryTreeNode and pBinaryTreeNode, respectively,
*		 data is set to newData
*	BinaryTreeNode (const BinaryTreeNode &copy)
*		l_child, r_child and data are set to the values of their counterparts
*		within copy
*	operator = (const BinaryTreeNode &copy)
*		Copies l_child, r_child and data from copy into the current BinaryTreeNode object
*	~BinaryTreeNode()
*		Deletes the BinaryTreeNode
*
* Methods:		
*	operator<<(ostream & out, const BinaryTreeNode<T> & nBinaryTreeNode)
*		Prints out the data stored in BinaryTreeNode to the given ostream
*	getData ( )
*		Returns data
*	getLChild ( )
*		Returns a pointer to l_child
*	getRChild ( )
*		Returns a pointer to r_child
*	setData (T newData)
*		sets data to newData
*	setLChild (const BinaryTreeNode * nBinaryTreeNode)
*		sets l_child to nBinaryTreeNode
*	setRChild (const BinaryTreeNode * pBinaryTreeNode)
*		sets r_child to pBinaryTreeNode
*************************************************************************/

template<typename T>
class BinaryTree;
template<typename T>
class Queue;
template<typename T>
class BinaryTreeNode;

/**********************************************************************	
* Purpose: Prints the data stored in the BinaryTreeNode object to the given 
*			output stream
*
* Entry: out is the output stream to be printed to, nBinaryTreeNode is the object
*			whose data will be printed
*
* Exit: data is printed to the out output stream
*
************************************************************************/
template<typename T>
ostream & operator<<(ostream & out, const BinaryTreeNode<T> & nBinaryTreeNode)
{
	if (!&nBinaryTreeNode)	
	{
		char error[] = "No data";
		throw error;
	}

	out << nBinaryTreeNode.getData();

	return out;
}

template<typename T>
class BinaryTreeNode
{ 
	friend class BinaryTree<T>;
	friend ostream & operator<< <>(ostream & out, const BinaryTreeNode<T> & nBinaryTreeNode);

private:
	void setData(T newData);
	void setLChild(BinaryTreeNode<T> * lBinaryTreeNode);
	void setRChild(BinaryTreeNode<T> * rBinaryTreeNode);

	BinaryTreeNode<T> * l_child;
	BinaryTreeNode<T> * r_child;
	T data;

public:
	BinaryTreeNode();
	BinaryTreeNode(T newData);
	BinaryTreeNode(T newData, BinaryTreeNode<T> * lBinaryTreeNode, BinaryTreeNode<T> * rBinaryTreeNode);
	BinaryTreeNode(const BinaryTreeNode<T> & copy);
	~BinaryTreeNode();
	BinaryTreeNode<T> & operator=(const BinaryTreeNode<T> & copy);

	const T & getData() const;
	BinaryTreeNode<T> * getLChild() const;
	BinaryTreeNode<T> * getRChild() const;
};

template<typename T>
bool operator==(const BinaryTreeNode<T> & fNode, const BinaryTreeNode<T> & lNode);

template<typename T>
bool operator==(const BinaryTreeNode<T> & fNode, const BinaryTreeNode<T> & lNode)
{
	bool ret = false;

	if (fNode.getData() == lNode.getData())
	{
		if (fNode.getLChild() == lNode.getLChild())
		{
			if (fNode.getRChild() == lNode.getRChild())
				ret = true;
		}
	}

	return ret;
}

/**********************************************************************	
* Purpose: Default constructor, initializes data to it's default value
*			l_child and r_child are set to nullptr
*
* Entry: No values are entered
*
* Exit: All variables within BinaryTreeNode are set to their default values
*
************************************************************************/
template<typename T>
BinaryTreeNode<T>::BinaryTreeNode() : data(), l_child(nullptr), r_child(nullptr)
{

}

/**********************************************************************	
* Purpose: Creates a new BinaryTreeNode with a given value for data
*
* Entry: newData is the value to be stored in data
*
* Exit: data is set to newData, l_child and r_child are set to nullptr
*
************************************************************************/
template<typename T>
BinaryTreeNode<T>::BinaryTreeNode(T newData) : data(newData), l_child(nullptr), r_child(nullptr)
{

}

/**********************************************************************	
* Purpose: Creates a new BinaryTreeNode object with values set for data, l_child
*			and r_child
*
* Entry: newData is the value to be stored in data, lBinaryTreeNode and rBinaryTreeNode
*			are the addresses to be stored in l_child and r_child, 
*			respectively
*
* Exit: All variables within BinaryTreeNode are initialized to the given values
*
************************************************************************/
template<typename T>
BinaryTreeNode<T>::BinaryTreeNode(T newData, BinaryTreeNode<T> * lBinaryTreeNode, BinaryTreeNode<T> * rBinaryTreeNode) : data(newData), l_child(lBinaryTreeNode), r_child(rBinaryTreeNode)
{

}

/**********************************************************************	
* Purpose: Copies the values stored within an existing BinaryTreeNode object into
*			a new BinaryTreeNode object
*
* Entry: copy is the existing BinaryTreeNode object to be copied
*
* Exit: data, l_child and r_child are set to the values of the same variables
*		within copy
*
************************************************************************/
template<typename T>
BinaryTreeNode<T>::BinaryTreeNode(const BinaryTreeNode & copy) : data(copy.getData()), l_child(copy.getLChild()), r_child(copy.getRChild())
{

}

/**********************************************************************	
* Purpose: Destroys the BinaryTreeNode object
*
* Entry: No values are entered
*
* Exit: No values are returned
*
************************************************************************/
template<typename T>
BinaryTreeNode<T>::~BinaryTreeNode()
{
	l_child = nullptr;
	r_child = nullptr;
	data = T();
}

/**********************************************************************	
* Purpose: Copies the values stored in one BinaryTreeNode object into another
*
* Entry: copy is the BinaryTreeNode object to be copied into the current BinaryTreeNode
*
* Exit: data, l_child, and r_child of the current BinaryTreeNode object are set to 
*			the corresponding values of the copy object
*
************************************************************************/
template<typename T>
BinaryTreeNode<T> & BinaryTreeNode<T>::operator=(const BinaryTreeNode<T> & copy)
{
	if (*this != *copy)
	{
		data = copy.getData();
		l_child = copy.getLChild();
		r_child = copy.getRChild();
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
const T & BinaryTreeNode<T>::getData() const
{
	return data;
}

/**********************************************************************	
* Purpose: Returns a pointer to l_child
*
* Entry: No values are entered
*
* Exit: The pointer to l_child is returned
*
************************************************************************/
template<typename T>
BinaryTreeNode<T> * BinaryTreeNode<T>::getLChild() const
{
	return l_child;
}

/**********************************************************************	
* Purpose: Returns a pointer to r_child
*
* Entry: No values are entered
*
* Exit: The pointer to r_child is returned
*
************************************************************************/
template<typename T>
BinaryTreeNode<T> * BinaryTreeNode<T>::getRChild() const
{
	return r_child;
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
void BinaryTreeNode<T>::setData(T newData)
{
	data = newData;
}

/**********************************************************************	
* Purpose: Points l_child to the given address
*
* Entry: lBinaryTreeNode is the pointer to be stored in l_child
*
* Exit: lBinaryTreeNode is stored in l_child
*
************************************************************************/
template<typename T>
void BinaryTreeNode<T>::setLChild(BinaryTreeNode<T> * lBinaryTreeNode)
{
	l_child = lBinaryTreeNode;
}

/**********************************************************************	
* Purpose: Points r_child to the given address
*
* Entry: rBinaryTreeNode is the address to be stored in r_child
*
* Exit: rBinaryTreeNode is stored in r_child
*
************************************************************************/
template<typename T>
void BinaryTreeNode<T>::setRChild(BinaryTreeNode<T> * rBinaryTreeNode)
{
	r_child = rBinaryTreeNode;
}

#endif
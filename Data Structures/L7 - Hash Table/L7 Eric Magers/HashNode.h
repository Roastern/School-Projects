/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 7
* Filename:			HashNode.h
* Date Created:		6/3/2014
* Modifications:	
*
************************************************************/

#ifndef HASHNODE_H_
#define HASHNODE_H_

/************************************************************************
* Class: HashNode
*
* Purpose: This class creates a node to store data in a HashTable object
*
* Manager functions:	
* 	HashNode ( )
*		Creates a HashNode object with default values
*	HashNode (K nKey, D nData)
*		Creates a HashNode object with nKey and nData stored
*	HashNode (const HashNode<K, D> & copy)
*		Creates a copy of the given HashNode object
*	operator= (const HashNode<K, D> & copy)
*		Copies the given HashNode object into the current one
*	~HashNode ( )
*		Restores variables stored in HashNode to their defaults
*
* Methods:		
*
*	getKey ( ) const
*		Returns the data stored in key
*	getData ( ) const
*		Returns the data stored in data
*	setKey (K nKey)
*		Stores nKey in key
*	setData (D nData)
*		Stores nData in data
*
*************************************************************************/

template<typename K, typename D>
class HashNode
{
private:
	K key;
	D data;

public:
	HashNode();
	HashNode(K nKey, D nData);
	HashNode(const HashNode<K, D> & copy);
	HashNode<K, D> & operator=(const HashNode<K, D> & copy);
	~HashNode();

	K getKey() const;
	D getData() const;
	void setKey(K nKey);
	void setData(D nData);
};

/**********************************************************************	
* Purpose: Default constructor, creates a HashNode with all variables
*			set to their default
*
* Entry: Nothing is passed into this function
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename K, typename D>
HashNode<K, D>::HashNode() : key(), data()
{

}

/**********************************************************************	
* Purpose: Creates a HashNode which stores the given data
*
* Entry: nKey is the value to be stored in key, nData is the value to be
*		 stored in data
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename K, typename D>
HashNode<K, D>::HashNode(K nKey, D nData) : key(nKey), data(nData)
{

}

/**********************************************************************	
* Purpose: Creates a copy of the given HashNode
*
* Entry: copy is the HashNode to be copied
*
* Exit: Nothing is returned, a new HashNode containing the same values
*		as copy is created
*
************************************************************************/
template<typename K, typename D>
HashNode<K, D>::HashNode(const HashNode<K, D> & copy) : key(copy.key), data(copy.data)
{

}

/**********************************************************************	
* Purpose: Copies the given HashNode into the curren HashNode
*
* Entry: copy is the HashNode to be copied
*
* Exit: A reference to the current HashNode is returned
*
************************************************************************/
template<typename K, typename D>
HashNode<K, D> & HashNode<K, D>::operator=(const HashNode<K, D> & copy)
{
	if (this != &copy)
	{
		key = copy.key;
		data = copy.data;
	}

	return *this;
}

/**********************************************************************	
* Purpose: Restores all data members to their default state
*
* Entry: Nothing is passed into this function
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename K, typename D>
HashNode<K, D>::~HashNode()
{
	key = K();
	data = D();
}

/**********************************************************************	
* Purpose: Returns key
*
* Entry: Nothing is passed into this function
*
* Exit: key is returned
*
************************************************************************/
template<typename K, typename D>
K HashNode<K, D>::getKey() const
{
	return key;
}

/**********************************************************************	
* Purpose: Returns data
*
* Entry: Nothing is passed into this function
*
* Exit: data is returned
*
************************************************************************/
template<typename K, typename D>
D HashNode<K, D>::getData() const
{
	return data;
}

/**********************************************************************	
* Purpose: Sets the value of key to the given value
*
* Entry: nKey is the value to be stored in key
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename K, typename D>
void HashNode<K, D>::setKey(K nKey)
{
	key = nKey;
}

/**********************************************************************	
* Purpose: Sets the value of data to the given value
*
* Entry: nData is the value to be stored in data
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename K, typename D>
void HashNode<K, D>::setData(D nData)
{
	data = nData;
}

#endif
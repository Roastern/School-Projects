/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 7
* Filename:			HashTable.h
* Date Created:		6/3/2014
* Modifications:	
*
************************************************************/

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include<vector>
#include<list>
#include "HashNode.h"
using std::vector;
using std::list;

/************************************************************************
* Class: HashTable
*
* Purpose: This class creates a HashTable 
*
* Manager functions:	
* 	HashTable ( )
*		Creates a HashTable object with an empty vector
*	HashTable (int size)
*		Creates a HashTable object with a vector containing the appropriate
*		number of elements
*	HashTable (int (*hash)(K key))
*		Creates a HashTable with the given hash function stored
*	HashTable (const HashTable<K, D> & copy)
*		Creates a copy of the given HashTable object
*	operator= (const HashTable<K, D> & copy)
*		Copies the given HashTable object into the current one
*	~HashTable ( )
*		Restores empties the vector stored in HashTable
*
* Methods:		
*
*	(*m_hash)(K key);
*		User defined hash function
*	Insert(K key, D data)
*		Creates a new hashnode with the provided data and inserts it
*		into table
*	Insert(HashNode<K, D> nuu)
*		Inserts the given HashNode into table
*	setHash(int (*hash)(K key))
*		Sets m_hash to be the given hash function
*	operator [] (K key)
*		Returns the data stored at the provided key value
*	Delete(K key)
*		Deletes the data stored at the provided key value
*	Traverse(void (*visit)(D data))
*		Traverses through the table of HashNodes performing the user
*		defined function on each of them
*
*************************************************************************/

template<typename K, typename D>
class HashTable
{
private:
	vector<list<HashNode<K, D>>> table;

public:
	HashTable();
	HashTable(int size);
	HashTable(int (*hash)(K key));
	HashTable(const HashTable<K, D> & copy);
	HashTable<K, D> & operator=(const HashTable<K, D> & copy);
	~HashTable();

	int (*m_hash)(K key);

	void Insert(K key, D data);
	void Insert(HashNode<K, D> nuu);
	void setHash(int (*hash)(K key));
	D operator [] (K key);
	void Delete(K key);
	void Traverse(void (*visit)(D data));
};


/**********************************************************************	
* Purpose: Default constructor, creates a HashNode with an empty table
*
* Entry: Nothing is passed into this function
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename K, typename D>
HashTable<K, D>::HashTable() : table(), m_hash(nullptr)
{

}

/**********************************************************************	
* Purpose: Creates a HashNode with a table of the given size
*
* Entry: Nothing is passed into this function
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename K, typename D>
HashTable<K, D>::HashTable(int size) : table(size), m_hash(nullptr)
{

}

/**********************************************************************	
* Purpose: Creates a HashNode with an empty table and stores the user
*			defined hash function in m_hash
*
* Entry: hash is the function to be pointed to by m_hash
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename K, typename D>
HashTable<K, D>::HashTable(int (*hash)(K key)) : table(), m_hash(hash)
{
	
}

/**********************************************************************	
* Purpose: Creates a copy of the given HashTable
*
* Entry: copy is the HashTable to be copied
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename K, typename D>
HashTable<K, D>::HashTable(const HashTable<K, D> & copy) : table(copy.table), m_hash(copy.m_hash)
{

}

/**********************************************************************	
* Purpose: Copies the table from the given HashTable into the current one
*
* Entry: copy is the HashTable to be copied
*
* Exit: A reference to the current HashTable is returned
*
************************************************************************/
template<typename K, typename D>
HashTable<K, D> & HashTable<K, D>::operator=(const HashTable<K, D> & copy)
{
	if (this != &copy)
	{
		table = copy.table;
		setHash(copy.m_hash);
	}

	return *this;
}

/**********************************************************************	
* Purpose: Returns the data stored in the table with the given key
*
* Entry: key is the specific key for the data to be returned
*
* Exit: The requested data is returned
*
************************************************************************/
template<typename K, typename D>
D HashTable<K, D>::operator[](K key)
{
	if (table.empty())
		throw "Table is empty, data not found";

	if (m_hash == nullptr)
		throw "No hash function defined";

	int container = m_hash(key);

	if (container > (int)table.size())
		throw "Key not found";

	bool run = true;
	D ret = D();
	
	for (list<HashNode<K, D>>::iterator i = table[container].begin(); (i != table[container].end()) && run; ++i)
	{
		if (key == (*i).getKey())
		{
			ret = (*i).getData();
			run = false;
		}
	}

	if (run == true)
		throw "Key not found";

	return ret;
}

/**********************************************************************	
* Purpose: Removes all HashNodes from table and sets it to it's default state
*
* Entry: Nothing is passed into this function
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename K, typename D>
HashTable<K, D>::~HashTable()
{
	m_hash = nullptr;
	table = vector<list<HashNode<K, D>>>();
}

/**********************************************************************	
* Purpose: sets m_hash to point to the user defined hash function
*
* Entry: hash is the user defined hash function
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename K, typename D>
void HashTable<K, D>::setHash(int (*hash)(K key))
{
	list<HashNode<K, D>> temp;
	m_hash = hash;

	for (int i = 0; i < (int)table.size(); i++)
	{
		for (list<HashNode<K, D>>::iterator j = table[i].begin(); (j != table[i].end()); ++j)
		{
			temp.push_back((*j));
		}
	}

	table = vector<list<HashNode<K, D>>>();

	for (list<HashNode<K, D>>::iterator i = temp.begin(); (i != temp.end()); ++i)
	{
		Insert((*i));
	}
}

/**********************************************************************	
* Purpose: Creates a new HashNode with the provided key and data and 
*			places it in the appropriate container within table
*
* Entry: key is the key and data is the data to be stored in the new
*		 HashNode
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename K, typename D>
void HashTable<K, D>::Insert(K key, D data)
{
	bool add = true;

	if (m_hash == nullptr)
		throw "No hash function defined";

	int container = m_hash(key);
	HashNode<K, D> newNode(key, data);

	if (container > (int)table.size())
	{
		for (int i = table.size(); i <= (container + 1); i++)
		{
			list<HashNode<K, D>> newlist;
			table.push_back(newlist);
		}
	}
	else
	{
		for (list<HashNode<K, D>>::iterator i = table[container].begin(); i != table[container].end(); ++i)
		{
			if (key == (*i).getKey())
			{
				add = false;
			}
		}
	}

	if (!add)
		throw "Key already exists in table";

	table[container].push_front(newNode);
}

/**********************************************************************	
* Purpose: Stores the provided HashNode in the appropriate container
*			within table
*
* Entry: nuu is the HashNode to be stored
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename K, typename D>
void HashTable<K, D>::Insert(HashNode<K, D> nuu)
{
	bool add = true;

	if (m_hash == nullptr)
		throw "No hash function defined";

	int container = m_hash(nuu.getKey());
	
	if (container > (int)table.size())
	{
		for (int i = table.size(); i <= (container + 1); i++)
		{
			list<HashNode<K, D>> newlist;
			table.push_back(newlist);
		}
	}
	else
	{
		for (list<HashNode<K, D>>::iterator i = table[container].begin(); i != table[container].end(); ++i)
		{
			if (nuu.getKey() == (*i).getKey())
			{
				add = false;
			}
		}
	}

	if (!add)
		throw "Key already exists in table";

	table[container].push_front(nuu);
}

/**********************************************************************	
* Purpose: Deletes the HashNode with the provided key from table
*
* Entry: key is the key to be searched for within the table
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename K, typename D>
void HashTable<K, D>::Delete(K key)
{
	if (m_hash == nullptr)
		throw "No hash function defined";
	if (table.empty())
		throw "Table is empty, data not found";

	int container = m_hash(key);

	if (container > (int)table.size())
		throw "Key not found";

	bool run = true;
	
	for (list<HashNode<K, D>>::iterator i = table[container].begin(); (i != table[container].end()) && run;)
	{
		if (key == (*i).getKey())
		{
			i = table[container].erase(i);
			run = false;
		}
		else
			++i;
	}

	if (run == true)
		throw "Key not found";
}

/**********************************************************************	
* Purpose: Traverses through the table and performs the user defined
*			function on each data stored within
*
* Entry: visit is the user defined function to be performed on all data
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename K, typename D>
void HashTable<K, D>::Traverse(void (*visit)(D data))
{
	if (table.size() == 0)
		throw "0 elements found";

	for (int i = 0; i < (int)table.size(); i++)
	{
		for (list<HashNode<K, D>>::iterator j = table[i].begin(); (j != table[i].end()); ++j)
		{
			visit((*j).getData());
		}
	}
}
#endif
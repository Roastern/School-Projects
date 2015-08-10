/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Assignment 11
* Filename:			Edge.h
* Date Created:		5/25/2014
* Modifications:	
*
************************************************************/

#ifndef EDGE_H_
#define EDGE_H

#include<list>
#include<string>
using std::list;
using std::string;

template<typename V, typename E>
class Vertex;

/************************************************************************
* Class: Edge
*
* Purpose: This class creates an Edge object to be stored in a Vertex
*
* Manager functions:	
* 	Edge ( )
* 		sets destination to nullptr, weight and ID to default values
*	Edge (const E & nID)
*		sets destination to nullptr, weight to it's default and ID to nID
*	Edge (Vertex<V, E> & nVertex, const int & nWeight)
*		sets destination to nVertex, weight to nWeight and ID to default
*	Edge (Vertex<V, E> & nVertex, const int & nWeight, const E & nID)
*		sets destination to nVertex, weight to nWeight and ID to nID
*	Edge (const Edge<V, E> & copy)
*		copies all data from copy into the new Edge
*	operator=(const Edge<V, E> & copy)
*		copies all data from copy into the current Edge
*	~Edge ( )
*		Resets all stored values to their defaults
*
* Methods:		
*
*	getWeight ( ) const
*		Returns weight
*	getID ( ) const
*		Returns ID
*	getDest ( ) const
*		Returns destination
*	setWeight (const int & nWeight)
*		Sets weight to nWeight
*	setID (const E & nID)
*		Sets ID to nID
*	setDest (Vertex<V, E> & nVertex)
*		Sets destination to nVertex
*************************************************************************/

template<typename V, typename E>
class Edge
{
	friend class Vertex<V, E>;

private:
	int weight;
	E ID;
	Vertex<V, E> * destination;

public:
	Edge();
	Edge(const E & nID);
	Edge(Vertex<V, E> & nVertex, const int & nWeight);
	Edge(Vertex<V, E> & nVertex, const int & nWeight, const E & nID);
	Edge(const Edge<V, E> & copy);
	Edge<V, E> & operator=(const Edge<V, E> & copy);
	~Edge();

	const int & getWeight() const;
	const E & getID() const;
	const Vertex<V, E> * getDest() const;

	void setWeight(const int & nWeight);
	void setID(const E & nID);
	void setDest(Vertex<V, E> & nVertex);
};

/**********************************************************************	
* Purpose: Compares two Edges to see if their ID's are the same
*
* Entry: e1 and e2 are the edges to be compared
*
* Exit: True is returned if the edges have the same ID, false if not
*
************************************************************************/
template<typename V, typename E>
bool operator==(const Edge<V, E> & e1, const Edge<V, E> & e2)
{
	bool ret = false;

	if (e1.getID() == e2.getID())
	{
		ret = true;
	}

	return ret;
}

/**********************************************************************	
* Purpose: Default constructor, all values are set to their default
*
* Entry: No values are passed into this function
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename V, typename E>
Edge<V, E>::Edge() : weight(), destination(nullptr), ID()
{

}

/**********************************************************************	
* Purpose: Creates an edge with the given ID
*
* Entry: nID is the ID to be stored in the new edge
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename V, typename E>
Edge<V, E>::Edge(const E & nID) : weight(), destination(nullptr), ID(nID)
{

}

/**********************************************************************	
* Purpose: Compares two Edges to see if their ID's are the same
*
* Entry: e1 and e2 are the edges to be compared
*
* Exit: True is returned if the edges have the same ID, false if not
*
************************************************************************/
template<typename V, typename E>
Edge<V, E>::Edge(Vertex<V, E> & nVertex, const int & nWeight) : weight(nWeight), destination(&nVertex), ID()
{

}

/**********************************************************************	
* Purpose: Creates a new edge with the given destination, weight and ID
*
* Entry: nVertex is the address to be stored in destination, nWeight is
*		 the int to be stored in weight, nID is the ID to be stored in ID
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename V, typename E>
Edge<V, E>::Edge(Vertex<V, E> & nVertex, const int & nWeight, const E & nID) : weight(nWeight), destination(&nVertex), ID(nID)
{

}

/**********************************************************************	
* Purpose: Creates a new edge with the same values as the copied edge
*
* Entry: copy is the edge to be copied
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename V, typename E>
Edge<V, E>::Edge(const Edge & copy) : weight(copy.weight), destination(copy.destination), ID(copy.ID)
{

}

/**********************************************************************	
* Purpose: Copies all data from one edge into the current edge
*
* Entry: copy is the edge to be copied
*
* Exit: A reference to the current edge is returned
*
************************************************************************/
template<typename V, typename E>
Edge<V, E> & Edge<V, E>::operator=(const Edge<V, E> & copy)
{
	if (this != &copy)
	{
		weight = copy.weight;
		destination = copy.destination;
		ID = copy.ID;
	}

	return *this;
}

/**********************************************************************	
* Purpose: Resets all data members to their default states
*
* Entry: Nothing is passed into this function
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename V, typename E>
Edge<V, E>::~Edge()
{
	weight = int();
	ID = E();
	destination = nullptr;
}

/**********************************************************************	
* Purpose: Returns the weight stored in the Edge
*
* Entry: Nothing is passed to this function
*
* Exit: weight is returned
*
************************************************************************/
template<typename V, typename E>
const int & Edge<V, E>::getWeight() const
{
	return weight;
}

/**********************************************************************	
* Purpose: Returns the ID stored in the Edge
*
* Entry: Nothing is passed to this function
*
* Exit: ID is returned
*
************************************************************************/
template<typename V, typename E>
const E & Edge<V, E>::getID() const
{
	return ID;
}

/**********************************************************************	
* Purpose: Returns the destination stored in the Edge
*
* Entry: Nothing is passed to this function
*
* Exit: destination is returned
*
************************************************************************/
template<typename V, typename E>
const Vertex<V, E> * Edge<V, E>::getDest() const
{
	return destination;
}

/**********************************************************************	
* Purpose: Sets weight to the given value
*
* Entry: nWeight is the data to be stored in weight
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename V, typename E>
void Edge<V, E>::setWeight(const int & nWeight)
{
	if (nWeight < 0)
		throw "Weight exceeds lower bounds";

	weight = nWeight;
}

/**********************************************************************	
* Purpose: Sets ID to the given value
*
* Entry: nID is the data to be stored in ID
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename V, typename E>
void Edge<V, E>::setID(const E & nID)
{
	ID = nID;
}

/**********************************************************************	
* Purpose: Sets destination to the given value
*
* Entry: nVertex is the data to be stored in destinationn
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename V, typename E>
void Edge<V, E>::setDest(Vertex<V, E> & nVertex)
{
	destination = &nVertex;
}

#endif
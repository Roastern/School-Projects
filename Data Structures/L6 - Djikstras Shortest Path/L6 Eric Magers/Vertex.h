/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Assignment 11
* Filename:			Vertex.h
* Date Created:		5/25/2014
* Modifications:	Changed addEdge to handle cases where
*					a duplicate edge was being added
*
************************************************************/

#ifndef VERTEX_H_
#define VERTEX_H_

#include "Edge.h"
#include <list>
#include <string>
using std::string;
using std::list;

template<typename V, typename E>
class Graph;

/************************************************************************
* Class: Vertex
*
* Purpose: This class creates an Vertex to be stored in Graph
*
* Manager functions:	
* 	Vertex ( )
* 		edges is initialized as an empty list of Edges, data is set to it's
*		default value, processed is set to false
*	Vertex (const V nData)
*		edges is initialized as an empty list of Edges, data is set to nData,
*		processed is set to false
*	Vertex (const V nData, list<Edge<V, E>> & nEdges)
*		nEdges is copied into edges, data is set to nData, processed to false
*	Vertex (const Vertex<V, E> & copy)
*		sets all data stored in copy to be copied into a new Vertex
*	operator=(const Vertex<V, E> & copy)
*		copies all data from copy into the current Vertex
*	~Vertex ( )
*		Resets all stored values to their defaults, clears edges
*
* Methods:		
*
*	getData ( ) const
*		Returns data
*	getEdges ( ) const
*		Returns a constant reference to the list of edges
*	isProcessed ( ) const
*		Determines whether or not this Vertex has been processed
*	setData (const V data)
*		Sets data to the input data
*	delEdge (E ID)
*		Deletes the Edge stored in edges with the given ID
*	addEdge (Edge<V, E> & nEdge)
*		Adds an Edge to edges
*	Process ( )
*		Either marks Vertex as processed or not processed
*************************************************************************/

template<typename V, typename E>
class Vertex
{
	friend class Graph<V, E>;
private:
	V data;
	bool processed;

public:
	Vertex();
	Vertex(const V nData);
	Vertex(const V nData, list<Edge<V, E>> & nEdges);
	Vertex(const Vertex<V, E> & copy);
	Vertex<V, E> & operator=(const Vertex<V, E> & copy);
	~Vertex();

	const V & getData() const;
	const list<Edge<V, E>> & getEdges() const;
	bool isProcessed() const;

	void setData(const V data);
	void delEdge(E ID);
	void addEdge(Edge<V, E> & nEdge);
	void Process();
	list<Edge<V, E>> edges;
};

/**********************************************************************	
* Purpose: Default constructor, sets all data members to default values
*
* Entry: Nothing is passed into this function.
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename V, typename E>
Vertex<V, E>::Vertex() : edges(), data(), processed(false)
{

}

/**********************************************************************	
* Purpose: Creates a new vertex which stores the given data
*
* Entry: nData is the data to be stored in data
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename V, typename E>
Vertex<V, E>::Vertex(const V nData) : edges(), data(nData), processed(false)
{

}

/**********************************************************************	
* Purpose: Creates a new vertex which stores the given data and edges
*
* Entry: nData is the data to be stored in data, nEdges is a list of
*		 edges to be stored in edges
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename V, typename E>
Vertex<V, E>::Vertex(const V nData, list<Edge<V, E>> & nEdges) : edges(), data(nData), processed(false)
{
	edges = nEdges;
}

/**********************************************************************	
* Purpose: Creates a new vertex which copies all the data from an 
*			existing vertex
*
* Entry: copy is the vertex to be copied
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename V, typename E>
Vertex<V, E>::Vertex(const Vertex<V, E> & copy) : edges(copy.edges), data(copy.data), processed(false)
{

}

/**********************************************************************	
* Purpose: Copies all the data members from a given vertex into the 
*			current vertex
*
* Entry: copy is the vertex to be copied
*
* Exit: A reference to the current vertex is returned
*
************************************************************************/
template<typename V, typename E>
Vertex<V, E> & Vertex<V, E>::operator=(const Vertex<V, E> & copy)
{
	if (this != &copy)
	{
		data = copy.data;
		edges = copy.edges;
	}

	return *this;
}

/**********************************************************************	
* Purpose: Resets all data members to their initial state
*
* Entry: Nothing is passed into this function
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename V, typename E>
Vertex<V, E>::~Vertex()
{
	data = V();
	edges.clear();
	processed = false;
}

/**********************************************************************	
* Purpose: Returns data
*
* Entry: Nothing is passed into this function
*
* Exit: Data is returned
*
************************************************************************/
template<typename V, typename E>
const V & Vertex<V, E>::getData() const
{
	return data;
}

/**********************************************************************	
* Purpose: Returns a constant list of all the edges
*
* Entry: Nothing is passed into this function
*
* Exit: A constant reference to edges is returned
*
************************************************************************/
template<typename V, typename E>
const list<Edge<V, E>> & Vertex<V, E>::getEdges() const
{
	return edges;
}

/**********************************************************************	
* Purpose: Returns the flag which determines whether or not the vertex
*		   is processed
*
* Entry: Nothing is passed into this function
*
* Exit: Either true or false is returned
*
************************************************************************/
template<typename V, typename E>
bool Vertex<V, E>::isProcessed() const
{
	return processed;
}

/**********************************************************************	
* Purpose: Sets data to the given value
*
* Entry: nData is the data to be stored in data
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename V, typename E>
void Vertex<V, E>::setData(const V nData)
{
	data = nData;
}

/**********************************************************************	
* Purpose: Deletes the Edge with the given ID from edges
*
* Entry: nID is the ID of the edge to be deleted
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename V, typename E>
void Vertex<V, E>::delEdge(const E dID)
{
	list<Edge<V, E>>::iterator i = edges.begin();
	int size = edges.size();
	bool deleted = false;

	if (size == 1)
	{
		if ((*i).getID() == dID)
		{
			i = edges.erase(i);
			deleted = true;
		}
	}
	else if (size > 1)
	{
		do
		{
			if ((*i).getID() == dID)
			{
				i = edges.erase(i);
				deleted = true;
			}
			else
				++i;
		}
		while (i != edges.end() && !deleted);
	}

	if (deleted == false)
		throw "Specified edge was not found";
}

/**********************************************************************	
* Purpose: Adds the given edge into the list of edges
*
* Entry: nEdge is the Edge to be added
*
* Exit: Nothing is returned, nEdge is added to edges
*
************************************************************************/
template<typename V, typename E>
void Vertex<V, E>::addEdge(Edge<V, E> & nEdge)
{
	bool added = false;

	if (edges.size() != 0)
	{
		for (list<Edge<V, E>>::iterator i = edges.begin(); (i != edges.end()) && !added; ++i)
		{
			if (nEdge.getID() == (*i).getID())
			{
				if (nEdge.getDest() == (*i).getDest())
				{
					(*i).setWeight(nEdge.getWeight());
					added = true;
				}
			}
		}
	}

	if (!added)
		edges.push_back(nEdge);
}

/**********************************************************************	
* Purpose: Flags the vertex as either processed or unprocessed
*
* Entry: Nothing is passed into this function
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename V, typename E>
void Vertex<V, E>::Process()
{
	if (processed == true)
		processed = false;
	else
		processed = true;
}

#endif
/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Assignment 11
* Filename:			Graph.h
* Date Created:		5/25/2014
* Modifications:	Updated add vertex so that no duplicate
*					vertices can be added
*					Added getWeight(), getPosition(), and
*					getVertex() to make the graph more 
*					user friendly
*					Updated to add findPath() between two
*					given vertices
*
************************************************************/

#ifndef GRAPH_H_
#define GRAPH_H_

#include "Vertex.h"
#include <list>
#include <iostream>
using std::cout;
using std::list;

/************************************************************************
* Class: Graph
*
* Purpose: This class creates a Graph which stores a list of vertices
*
* Manager functions:	
* 	Graph ( )
* 		graph is initialized to an empty list of vertices, count to 0,
*	Graph (const Vertex<V, E> & nVertex)
*		Initializes graph with nVertex stored in the list, count to 1
*	Graph (constGraph<V, E> & copy)
*		sets all data stored in copy to be copied into a new Graph
*	operator=(const Graph<V, E> & copy)
*		copies all data from copy into the current Graph
*	~Graph ( )
*		Resets all stored values to their defaults, clears edges
*
* Methods:		
*
*	InsertVertex (V data)
*		Creates a new Vertex with the given data and stores it in graph
*	DeleteVertex (V data)
*		Finds a vertex with the given data and removes it from graph
*	InsertArc (V data1, V data2, E edgeID)
*		Inserts an edge connecting the given vertices
*	InsertArc (V data1, V data2, E edgeID, int edgeWeight)
*		Inserts an edge with the given weight connecting the given vertices
*	DeleteArc (V data1, V data2, E edgeID)
*		Deletes the given edge connecting the given vertices
*	DepthFirst ( )
*		Prints the graph in the depth first fashion
*	BreadthFirst ( )
*		Prints the graph in the breadth first fashion
*	getCount ( ) const
*		Returns count
*	isEmpty ( ) const
*		Determines whether or not the Graph is empty
*	visit (Vertex<V, E> * vVertex)
*		Performs an operation on the given vertex
*	unprocess ( )
*		Flags all vertices in graph to not processed
*	getWeight (V data, E edgeID)
*		Returns the weight of the edge in the given vertex
*	getPosition (V data)
*		Returns the position of the vertex in the graph
*	getVertex (int position)
*		Returns a reference to the vertex at the given position
*	findPath (V data1, V data2)
*		Returns a constant reference to the edge connecting the given
*		vertices
*************************************************************************/

template<typename V, typename E>
class Graph
{
private:
	list<Vertex<V, E>> graph;
	int count;

	void visit(Vertex<V, E> * vVertex);

public:
	Graph();
	Graph(const Vertex<V, E> & nVertex);
	Graph(const Graph<V, E> & copy);
	Graph<V, E> & operator=(const Graph<V, E> & copy);
	~Graph();

	void InsertVertex(V data);
	void DeleteVertex(V data);
	void InsertArc(V data1, V data2, E edgeID);
	void InsertArc(V data1, V data2, E edgeID, int edgeWeight);
	void DeleteArc(V data1, V data2, E edgeID);
	void DepthFirst();
	void BreadthFirst();

	int getCount() const;
	int getWeight(V data, E edgeID);
	int getPosition(V data);
	Vertex<V, E> & getVertex(int position);
	const Edge<V, E> & findPath(V data1, V data2);
	bool isEmpty() const;
	void unprocess();
};

/**********************************************************************	
* Purpose: Default constructor, creates an empty Graph
*
* Entry: Nothing is passed into this function
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename V, typename E>
Graph<V, E>::Graph() : graph(), count()
{

}

/**********************************************************************	
* Purpose: Creates a new Graph which stores the given Vertex
*
* Entry: nVertex is the vertex to be stored in the new Graph
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename V, typename E>
Graph<V, E>::Graph(const Vertex<V, E> & nVertex) : graph(), count(1)
{
	graph.push_back(nVertex);
}

/**********************************************************************	
* Purpose: Creates a new graph which stored a copy of the list stored 
*			in the given Graph
*
* Entry: copy is the Graph to be copied
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename V, typename E>
Graph<V, E>::Graph(const Graph<V, E> & copy) : graph(copy.graph), count(copy.count)
{

}

/**********************************************************************	
* Purpose: Copies the list of vertices from the given Graph to the current one
*
* Entry: copy is the graph to be copied
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename V, typename E>
Graph<V, E> & Graph<V, E>::operator=(const Graph<V, E> & copy)
{
	if (this != &copy)
	{
		graph = copy.graph;
		count = copy.count;
	}

	return *this;
}

/**********************************************************************	
* Purpose: Deletes all vertices from graph
*
* Entry: Nothing is passed into this function
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename V, typename E>
Graph<V, E>::~Graph()
{
	graph.clear();
	count = 0;
}

/**********************************************************************	
* Purpose: Inserts a vertex into graph which the given data
*
* Entry: nData is the data to be stored in the vertex
*
* Exit: Nothing is returned, the specified vertex is created
*
************************************************************************/
template<typename V, typename E>
void Graph<V, E>::InsertVertex(V nData)
{
	bool added = false;
	for (list<Vertex<V, E>>::iterator i = graph.begin(); i != graph.end() && !added; ++i)
	{
		if ((*i).getData() == nData)
			added = true;
	}

	if (added)
		throw "Specified vertex is already in the graph";

	Vertex<V, E> temp(nData);
	graph.push_back(temp);
	count++;
}

/**********************************************************************	
* Purpose: Deletes the given vertex from graph
*
* Entry: nData is the data stored in the vertex which is to be deleted
*
* Exit: Nothing is returned, the specified vertex is deleted
*
************************************************************************/
template<typename V, typename E>
void Graph<V, E>::DeleteVertex(V nData)
{
	list<Vertex<V, E>>::iterator i = graph.begin();
	bool erased = false;
	int c = 0;

	if (graph.empty())
		throw "No data found, cannot delete";

	do
	{
		if ((*i).getData() == nData)
		{
			list<Edge<V, E>>::iterator b = (*i).edges.begin();
			bool d2 = false;
			int e = 0;
			for (; b != (*i).edges.end() && !d2; ++b)
			{
				if ((*b).getDest()->getData() == (*i).getData())
				{
					b = (*i).edges.erase(b);
					d2 = true;
				}
			}

			i = graph.erase(i);
			erased = true;
		}
		else
			++i;
	}
		while (i != graph.end() && !erased);

	if (!erased)
		throw "Specified Vertex does not exist";
}

/**********************************************************************	
* Purpose: Creates a pair of edges between the given vertices with the
*			specified weight
*
* Entry: data1 and data2 are the datas of the vertices between which the
*		 edge is to be created, edgeID is the ID to be stored in the new edges
*
* Exit: An arc between the specified vertices is created, nothing is returned
*
************************************************************************/
template<typename V, typename E>
void Graph<V, E>::InsertArc(V data1, V data2, E edgeID)
{
	bool v1b = false;
	bool v2b = false;
	bool first = false;

	list<Vertex<V, E>>::iterator v1 = graph.begin();
	list<Vertex<V, E>>::iterator v2 = graph.begin();

	if (graph.size() != 0)
	{
		for (int i = 0; (i < count) || (!v2b && !v1b); i++)
		{
			if ((*v1).getData() == data1 && !v1b)
			{
				v1b = true;
			}
			else if (!v1b)
				++v1;

			if ((*v2).getData() == data2 && !v2b)
			{
				v2b = true;
			}
			else if (!v2b)
				++v2;
		}
	}
	else 
		first = true;

	if (v1b == false && first == true)
	{
		InsertVertex(data1);
		v1 = graph.begin();
	}
	else if (v1b == false)
	{
		InsertVertex(data1);
		v1 = graph.end();
	}

	if (v2b == false && first == true)
	{
		InsertVertex(data2);
		v2 = graph.end();
		--v2;
	}
	else if (v2b == false)
	{
		InsertVertex(data2);
		v2 = graph.end();
		--v2;
	}

	Edge<V, E> temp1(edgeID);
	temp1.setDest(*v2);

	Edge<V, E> temp2(edgeID);
	temp2.setDest(*v1);

	(*v1).addEdge(temp1);
	(*v2).addEdge(temp2);
}

/**********************************************************************	
* Purpose: Creates a pair of edges between the given vertices with the
*			specified weight
*
* Entry: data1 and data2 are the datas of the vertices between which the
*		 edge is to be created, edgeID is the ID and edgeWeight is the 
*		 weight to be stored in the new edges
*
* Exit: An arc between the specified vertices is created, nothing is returned
*
************************************************************************/
template<typename V, typename E>
void Graph<V, E>::InsertArc(V data1, V data2, E edgeID, int edgeWeight)
{
	bool v1b = false;
	bool v2b = false;
	bool first = false;

	list<Vertex<V, E>>::iterator v1 = graph.begin();
	list<Vertex<V, E>>::iterator v2 = graph.begin();

	if (graph.size() != 0)
	{
		for (int i = 0; (i < count) || (!v2b && !v1b); i++)
		{
			if ((*v1).getData() == data1 && !v1b)
			{
				v1b = true;
			}
			else if (!v1b)
				++v1;

			if ((*v2).getData() == data2 && !v2b)
			{
				v2b = true;
			}
			else if (!v2b)
				++v2;
		}
	}
	else
		first = true;

	if (v1b == false && first == true)
	{
		InsertVertex(data1);
		v1 = graph.begin();
	}
	else if (v1b == false)
	{
		InsertVertex(data1);
		v1 = graph.end();
	}

	if (v2b == false && first == true)
	{
		InsertVertex(data2);
		v2 = graph.end();
		--v2;
	}
	else if (v2b == false)
	{
		InsertVertex(data2);
		v2 = graph.end();
		--v2;
	}

	Edge<V, E> temp1((*v2), edgeWeight, edgeID);
	Edge<V, E> temp2((*v1), edgeWeight, edgeID);

	v1->addEdge(temp1);
	v2->addEdge(temp2);
}

/**********************************************************************	
* Purpose: Deletes the specified edges between two vertices
*
* Entry: data1 and data2 are the vertices where the edge exists, edgeID
*		 is the ID of the edges to be deleted
*
* Exit: Nothing is returned, the specified edge is deleted
*
************************************************************************/
template<typename V, typename E>
void Graph<V, E>::DeleteArc(V data1, V data2, E edgeID)
{
	bool v1b = false;
	bool v2b = false;

	list<Vertex<V, E>>::iterator v1 = graph.begin();
	list<Vertex<V, E>>::iterator v2 = graph.begin();

	for (int i = 0; (i < count) || (!v2b && !v1b); i++)
	{
		if ((*v1).getData() == data1 && !v1b)
		{
			v1b = true;
		}
		else if (!v1b)
			++v1;

		if ((*v2).getData() == data2 && !v2b)
		{
			v2b = true;
		}
		else if (!v2b)
			++v2;
	}

	if (v1b == false)
		throw "Starting Vertex does not exist";
	if (v2b == false)
		throw "Ending Vertex does not exist";

	(*v1).delEdge(edgeID);
	(*v2).delEdge(edgeID);

	count--;
}

/**********************************************************************	
* Purpose: Performs the breadth-first traversal on graph
*
* Entry: Nothing is passed into this function
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename V, typename E>
void Graph<V, E>::BreadthFirst()
{
	if (isEmpty())
		throw "Graph is empty, cannot traverse";
	
	list<Vertex<V, E> *> tempL;
	Vertex<V, E> * tempV = &graph.front();

	tempL.push_front(tempV);

	do
	{
		tempV = tempL.front();

		if (!tempV->isProcessed())
			visit(tempV);

		tempL.pop_front();

		for (list<Edge<V, E>>::iterator i = tempV->edges.begin(); i != tempV->edges.end(); ++i)
		{
			if (!((*i).getDest()->isProcessed()))
			{
				tempL.push_back(const_cast<Vertex<V, E> *>((*i).getDest()));
			}
		}
	} while (!tempL.empty());

	unprocess();
}

/**********************************************************************	
* Purpose: Performs the depth-first traversal on graph
*
* Entry: Nothing is passed into this function
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename V, typename E>
void Graph<V, E>::DepthFirst()
{
	if (graph.empty())
		throw "Graph is empty, cannot traverse";

	list<Vertex<V, E> *> tempL;
	Vertex<V, E> * tempV = &graph.front();

	tempL.push_back(tempV);

	do
	{
		tempV = tempL.back();

		if (!tempV->isProcessed())
			visit(tempV);

		tempL.pop_back();

		for (list<Edge<V, E>>::iterator i = tempV->edges.begin(); i != tempV->edges.end(); ++i)
		{
			if (!((*i).getDest()->isProcessed()))
			{
				tempL.push_back(const_cast<Vertex<V, E> *>((*i).getDest()));
			}
		}
	} while (!tempL.empty());

	unprocess();
}

/**********************************************************************	
* Purpose: Returns the number of Vertices stored in graph
*
* Entry: Nothing is passed into this function
*
* Exit: The number of vertices stored in graph is returned
*
************************************************************************/
template<typename V, typename E>
int Graph<V, E>::getCount() const
{
	return count;
}

/**********************************************************************	
* Purpose: Determines whether or not the graph is empty
*
* Entry: Nothing is passed into this function
*
* Exit: Either true or false is returned
*
************************************************************************/
template<typename V, typename E>
bool Graph<V, E>::isEmpty() const
{
	bool empty = false;

	if (graph.size() == 0)
		empty = true;

	return empty;
}

/**********************************************************************	
* Purpose: Performs a specific function on the specified vertex
*
* Entry: vVertex is the Vertex to be processed
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename V, typename E>
void Graph<V, E>::visit(Vertex<V, E> * vVertex)
{
	cout << vVertex->getData() << endl;
	vVertex->Process();
}

/**********************************************************************	
* Purpose: Flags all vertices stored in graph as unprocessed
*
* Entry: Nothing is passed into this function
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename V, typename E>
void Graph<V, E>::unprocess()
{
	if (!graph.empty())
	{
		for (list<Vertex<V, E>>::iterator i = graph.begin(); i != graph.end(); ++i)
		{
			if ((*i).isProcessed())
				(*i).Process();
		}
	}
}

/**********************************************************************	
* Purpose: Returns the weight of the specified edge
*
* Entry: data is the data of the vertex to be searched, edgeID is the ID
*		 of the edge whose weight is to be returned
*
* Exit: The weight of the specified Edge is returned, if found
*
************************************************************************/
template<typename V, typename E>
int Graph<V, E>::getWeight(V data, E edgeID)
{
	bool loop1 = true;
	bool loop2 = true;
	int ret = 0;
	int position = 0;

	for (list<Vertex<V, E>>::iterator i = graph.begin(); (position < count) && loop1; ++i)
	{
		if ((*i).getData() == data)
		{
			loop1 = false;
			for (list<Edge<V, E>>::iterator l = (*i).edges.begin(); l != (*i).edges.end() && loop2; ++l)
			{
				if ((*l).getID() == edgeID)
				{
					loop2 = false;
					ret = (*l).getWeight();
				}			
			}
		}
		position++;
	}
	if (loop1)
		throw "Specified Vertex was not found";
	else if (loop2)
		throw "Specified Edge was not found";

	return ret;
}

/**********************************************************************	
* Purpose: Returns the position of the specified vertex
*
* Entry: data is the data value of the vertex to be found
*
* Exit: The position in the list of the specified vertex is returned
*
************************************************************************/
template<typename V, typename E>
int Graph<V, E>::getPosition(V data)
{
	int position = 0;
	bool loop = true;

	for (list<Vertex<V, E>>::iterator i = graph.begin(); (position < count) && loop; ++i)
	{
		if ((*i).getData() == data)
		{
			loop = false;
		}
		else
			position++;
	}

	if (loop)
		throw "Specified Vertex not found";

	return position;
}

/**********************************************************************	
* Purpose: Returns a reference to the given vertex
*
* Entry: position is the location in the list where the required vertex
*		 is located
*
* Exit: The specified vertex is returned
*
************************************************************************/
template<typename V, typename E>
Vertex<V, E> & Graph<V, E>::getVertex(int position)
{
	int cur = 0;
	bool loop = true;

	if (position >= count)
		throw "Specified position exceeds upper bounds";
	if (position < 0)
		throw "Specified position exceeds lower bounds";

	list<Vertex<V, E>>::iterator i = graph.begin();

	for (; (cur < count) && loop;)
	{
		if (cur == position)
		{
			loop = false;
		}
		else
		{
			cur++;
			++i;
		}
	}

	return (*i);
}

/**********************************************************************	
* Purpose: Returns a constant reference to the Edge between the given
*			vertices
*
* Entry: data1 and data2 are the datas stored in the vertices which there
*		 is supposed to be an Edge between
*
* Exit: If existing, a path between the given vertices is returned
*
************************************************************************/
template<typename V, typename E>
const Edge<V, E> & Graph<V, E>::findPath(V data1, V data2)
{
	int position = 0;
	bool loop = true;
	Edge<V, E> * tempE = nullptr;

	for (list<Vertex<V, E>>::iterator i = graph.begin(); (position < count) && loop; ++i)
	{
		if ((*i).getData() == data1)
		{
			for (list<Edge<V, E>>::iterator j = (*i).edges.begin(); (j != (*i).edges.end()) && loop; ++j)
			{
				const Vertex<V, E> * temp = (*j).getDest();
				if (temp->getData() == data2)
				{
					tempE = &(*j);
					loop = false;
				}
			}
			loop = false;
		}
		else
			position++;
	}

	if (loop)
		throw "Specified Vertex pair not found";

	return *tempE;
}

#endif
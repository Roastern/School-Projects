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
*************************************************************************/

template<typename V, typename E>
class Graph
{
private:
	list<Vertex<V, E>> graph;
	int count;

	void visit(Vertex<V, E> * vVertex);
	void unprocess();

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
	bool isEmpty() const;
};

template<typename V, typename E>
Graph<V, E>::Graph() : graph(), count()
{

}

template<typename V, typename E>
Graph<V, E>::Graph(const Vertex<V, E> & nVertex) : graph(), count(1)
{
	graph.push_back(nVertex);
}

template<typename V, typename E>
Graph<V, E>::Graph(const Graph<V, E> & copy) : graph(copy.graph), count(copy.count)
{

}

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

template<typename V, typename E>
Graph<V, E>::~Graph()
{
	graph.clear();
	count = 0;
}

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

template<typename V, typename E>
void Graph<V, E>::InsertArc(V data1, V data2, E edgeID)
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
	{
		InsertVertex(data1);
		v1 = graph.end();
	}

	if (v2b == false)
	{
		InsertVertex(data2);
		v2 = graph.end();
	}

	Edge<V, E> temp1(edgeID);
	temp1.setDest(*v2);

	Edge<V, E> temp2(edgeID);
	temp2.setDest(*v1);

	(*v1).addEdge(temp1);
	(*v2).addEdge(temp2);
}

template<typename V, typename E>
void Graph<V, E>::InsertArc(V data1, V data2, E edgeID, int edgeWeight)
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
	{
		InsertVertex(data1);
		v1 = graph.end();
	}

	if (v2b == false)
	{
		InsertVertex(data2);
		v2 = graph.end();
	}

	Edge<V, E> temp1(*v2, edgeWeight, edgeID);
	Edge<V, E> temp2(*v1, edgeWeight, edgeID);

	v1->addEdge(temp1);
	v2->addEdge(temp2);
}

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

template<typename V, typename E>
int Graph<V, E>::getCount() const
{
	return count;
}

template<typename V, typename E>
bool Graph<V, E>::isEmpty() const
{
	bool empty = false;

	if (graph.size() == 0)
		empty = true;

	return empty;
}

template<typename V, typename E>
void Graph<V, E>::visit(Vertex<V, E> * vVertex)
{
	cout << vVertex->getData() << endl;
	vVertex->Process();
}

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

#endif
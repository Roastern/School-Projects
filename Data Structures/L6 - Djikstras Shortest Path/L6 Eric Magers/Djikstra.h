/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 6
* Filename:			Djikstra.h
* Date Created:		6/2/2014
* Modifications:	
*
************************************************************/

#ifndef DJIKSTRA_H_
#define DJIKSTRA_H_

#include <iostream>
#include "Graph.h"
#include <list>
using std::cout;
using std::cin;
using std::endl;

/************************************************************************
* Class: Djikstra
*
* Purpose: This class performs the performs Djikstras algorithm on the 
*			given Graph
*
* Manager functions:	
* 	Djikstra ( )
*		Creates a new Djikstra object with default values 
*	Djikstra(Graph<V, E> * nGraph)
*		Creates a new Djikstra object with the given Graph stored in it
*	Djikstra(const Djikstra<V, E> & copy)
*		Creates a new Djikstra object which copies the data members from copy
*	Djikstra & operator=(const Djikstra<V, E> & copy)
*		Copies all data members within copy and stores it in the current object
*	~Djikstra ( )
*		Resets all the data members within the Djikstra object to their 
*		default values
*
* Methods:		
*
*	getStart ( )
*		Gets the starting vertex from the user
*	findShortestPath ( )
*		Finds the shortest path between the starting vertex and all others
*	getDest ( )
*		Gets the ending vertex from the user
*	printRoute ( )
*		Prints the shortest route from the starting vertex to the end
*	populateArrays ( )
*		Initializes all arrays to -1s
*************************************************************************/
template<typename V, typename E>
class Djikstra
{
private:
	Graph<V, E> * graph;
	int * distance;
	int * position;

	int curPos;
	int destPos;
	int startPos;

	void populateArrays();

public:
	Djikstra();
	Djikstra(Graph<V, E> * nGraph);
	Djikstra(const Djikstra<V, E> & copy);
	Djikstra & operator=(const Djikstra<V, E> & copy);
	~Djikstra();

	void getStart();
	void findShortestPath();
	void getDest();
	void printRoute();
};

/**********************************************************************	
* Purpose: Creates a Djikstra object with all data members initialized to
*			their default value
*
* Entry: Nothing is passed into this function
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename V, typename E>
Djikstra<V, E>::Djikstra() : startPos(-1), curPos(-1), destPos(-1), position(nullptr), 
							 distance(nullptr), graph(nullptr)
{

}

/**********************************************************************	
* Purpose: Creates a Djikstra object with the given Graph stored in it
*			and all other data members set to default values
*
* Entry: nGraph is a pointer to a Graph to be stored in the Djikstra object
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename V, typename E>
Djikstra<V, E>::Djikstra(Graph<V, E> * nGraph) : startPos(-1), curPos(-1), destPos(-1), 
												 position(nullptr), distance(nullptr), graph(nGraph)
{

}

/**********************************************************************	
* Purpose: Creates a new Djikstra object with all data members values 
*			copied from the given object
*
* Entry: copy is the Djikstra object to be copied
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename V, typename E>
Djikstra<V, E>::Djikstra(const Djikstra<V, E> & copy) : startPos(copy.startPos), curPos(copy.curPos), destPos(copy.destPos), 
														graph(copy.graph)
{
	position = new int[graph->getCount()];
	distance = new int[graph->getCount()];

	for (int i = 0; i < graph.getCount(); i++)
	{
		position[i] = copy.position[i];
		distance[i] = copy.distance[i];
	}
}

/**********************************************************************	
* Purpose: Copies all data member variables from copy into the current
*			Djikstra object
*
* Entry: copy is the Djikstra object to be copied
*
* Exit: A reference to the current object is returned
*
************************************************************************/
template<typename V, typename E>
Djikstra<V, E> & Djikstra<V, E>::operator=(const Djikstra<V, E> & copy)
{
	if (this != & copy)
	{
		curPos = copy.curPos;
		destPos = copy.destPos;
		startPos = copy.startPos;
		delete [] position;
		delete [] distance;
		graph = copy.graph;

		position = new int[graph->getCount()];
		distance = new int[graph->getCount()];

		for (int i = 0; i < graph.getCount(); i++)
		{
			position[i] = copy.position[i];
			distance[i] = copy.distance[i];
		}
	}

	return *this;
}

/**********************************************************************	
* Purpose: Resets all data members to their default values
*
* Entry: Nothing is passed into this function
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename V, typename E>
Djikstra<V, E>::~Djikstra()
{
	startPos = -1;
	curPos = -1;
	destPos = -1;
	delete [] position;
	delete [] distance;
	position = nullptr;
	distance = nullptr;
	graph = nullptr;
}

/**********************************************************************	
* Purpose: Populates the position and distance arrays to -1
*
* Entry: Nothing is passed into this function
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename V, typename E>
void Djikstra<V, E>::populateArrays()
{
	delete [] position;
	delete [] distance;

	int end = graph->getCount();
	position = nullptr;
	distance = nullptr;

	position = new int[end];
	distance = new int[end];

	for (int i = 0; i < end; i++)
	{
		position[i] = -1;
		distance[i] = -1;
	}

	if (graph != nullptr)
		graph->unprocess();
}

/**********************************************************************	
* Purpose: Gets the starting vertex from the user
*
* Entry: Nothing is passed into this function
*
* Exit: Nothing is returned, findShortestPath() is called
*
************************************************************************/
template<typename V, typename E>
void Djikstra<V, E>::getStart()
{
	V sData;
	curPos = -1;

	while (curPos == -1)
	{
		cout << "Please enter the vertex from which you would like to start: " << endl;
		getline(cin, sData);

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(100, '\n');
		}

		try
		{
			curPos = graph->getPosition(sData);
		}
		catch (char * msg)
		{
			cout << msg << endl;
			curPos = -1;
		}
	}

	startPos = curPos;
	findShortestPath();
}

/**********************************************************************	
* Purpose: Gets the destination vertex from the user
*
* Entry: Nothing is passed into this function
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename V, typename E>
void Djikstra<V, E>::getDest()
{
	V sData;
	destPos = -1;

	while (destPos == -1)
	{
		cout << "Please enter the vertex at which you would like to end at: " << endl;
		getline(cin, sData);

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(100, '\n');
		}

		try
		{
			destPos = graph->getPosition(sData);
		}
		catch (char * msg)
		{
			cout << msg << endl;
			curPos = -1;
		}
	}
}

/**********************************************************************	
* Purpose: Finds the shortest paths between the starting vertices 
*			and all other vertices
*
* Entry: Nothing is passed into this function
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename V, typename E>
void Djikstra<V, E>::findShortestPath()
{
	populateArrays();
	Vertex<V, E> * temp = nullptr;
	int tempPos;
	int tempWeight;
	bool run = true;

	distance[curPos] = 0;
	position[curPos] = 0;

	while (run)
	{
		temp = &(graph->getVertex(curPos));
		for (list<Edge<V, E>>::iterator i = temp->edges.begin(); i != temp->edges.end(); ++i)
		{
			if (!(*i).getDest()->isProcessed())
			{
				tempPos = graph->getPosition((*i).getDest()->getData());
				tempWeight = (*i).getWeight() + distance[curPos];

				if ((distance[tempPos] == -1) || (distance[tempPos] > tempWeight))
				{
					distance[tempPos] = tempWeight;
					position[tempPos] = curPos;
				}
			}
		}

		temp->Process();

		run = false;

		for (int i = 0; i < graph->getCount() && !run; i++)
		{
			temp = &(graph->getVertex(i));
			if (!(temp->isProcessed()) && (distance[i] != -1))
			{
				run = true;
				curPos = i;
			}
		}

		for (int i = curPos + 1; (i < graph->getCount()) && run; i++)
		{
			if ((distance[curPos] > distance[i]) && (distance[i] != -1))
			{
				temp = &(graph->getVertex(i));

				if (!(temp->isProcessed()))
				{
					curPos = i;
				}
			}
		}
	}
}

/**********************************************************************	
* Purpose: Prints the shortest route between the starting and ending
*		   vertices
*
* Entry: Nothing is passed into this function
*
* Exit: Nothing is returned
*
************************************************************************/
template<typename V, typename E>
void Djikstra<V, E>::printRoute()
{
	system("CLS");

	int totalWeight = 0;
	float travelTime = 0;
	curPos = destPos;

	list<int> stak;

	while (curPos != startPos)
	{
		stak.push_back(curPos);
		curPos = position[curPos];
	}

	Vertex<V, E> & temp1 = graph->getVertex(curPos);

	if (stak.size() == 0)
	{
		cout << "Start and destination are the same" << endl;
	}
	else
	{
		cout << "Starting at: " << temp1.getData() << endl << endl;

		while(stak.size())
		{
			curPos = stak.back();
			stak.pop_back();

			Vertex<V, E> & temp2 = graph->getVertex(curPos);
			const Edge<V, E> & tEdge = graph->findPath(temp1.getData(), temp2.getData());

			cout << "Take " << tEdge.getID() << " for " << tEdge.getWeight() << " miles to arrive at " << temp2.getData() << endl << endl;
			totalWeight = totalWeight + tEdge.getWeight();

			if (tEdge.getID() == "I-5")
			{
				travelTime = travelTime + (tEdge.getWeight() / 65);
			}
			else
			{
				travelTime = travelTime + ((float)tEdge.getWeight() / (float)55);
			}

			temp1 = temp2;
		}

		cout << "Total trip mileage: " << totalWeight << endl;
		cout << "Total travel time: " << travelTime << " hours" << endl;
	}
}
#endif
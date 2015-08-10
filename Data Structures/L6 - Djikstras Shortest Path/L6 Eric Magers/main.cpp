/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 6
* Filename:			main.cpp
* Date Created:		6/2/2014
* Modifications:	
*
* Overview:
*	This program populates a graph with cities, junctions and roads
*	and then allows the user to specify vertices from which the shortest
*	connecting path is found and printed
*
* Input:
*	The first set of input is from a file which populates the graph, data
*	in this file is deliminated by commas in the order of start vertex, 
*	end vertex, edge ID, edge weight
*
*	Input is received directly from the user then for the start vertex and
*	end vertex, which both have to be entered in exactly as it was input from the 
*	file.
*
* Output:
*	The output of this program will consist of prompts asking the user
*	for the start and ending vertices for the trip, and then the shortest
*	route which can be taken in the following format:
*
*	Starting at: [City/Junction name]
*	
*	Take [path name] for [number of miles] to arrive at [city/junction name]
*
*	Total trip mileage: [total number of miles]
*	Total trip time: [total number of miles divided by the speed limit]
*
************************************************************/

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Djikstra.h"
using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::ifstream;
using std::istringstream;

/**********************************************************************	
* Purpose: Populates the given Graph with the data stored in the lab06.txt file
*
* Entry: nGraph is the Graph to be populated
*
* Exit: Nothing is returned
*
************************************************************************/
void populateGraph(Graph<string, string> & nGraph);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Graph<string, string> map;
	populateGraph(map);

	Djikstra<string, string> pathfinder(&map);

	pathfinder.getStart();
	pathfinder.getDest();
	pathfinder.printRoute();

	char c;
	cin >> c;

	return 0;
}

void populateGraph(Graph<string, string> & nGraph)
{
	string line;
	string start;
	string end;
	string path;
	int miles;

	ifstream routes("lab06.txt");

	if (routes.is_open())
	{
		while (getline(routes, line))
		{
			istringstream whole(line);
			getline(whole, start, ',');
			getline(whole, end, ',');
			getline(whole, path, ',');
			getline(whole, line, ',');
			miles = atoi(line.c_str());

			nGraph.InsertArc(start, end, path, miles);
		}
	}
}
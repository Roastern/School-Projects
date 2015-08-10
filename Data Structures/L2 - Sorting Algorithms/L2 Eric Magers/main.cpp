/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 2
* Filename:			main.cpp
* Date Created:		4/10/2014
* Modifications:	
*
* Overview:
*	This program will generates arrays of a user specified
*	size filled with random, unsorted values. The program
*	then runs various sorting algorithms and prints the 
*	sorted arrays and the time it too for the algorithms
*	to run.
*
* Input:
*	The input for this program is an integer value passed
*	in from the command line
*
* Output:
*	The output of this program will be placed into the file
*	"Sorts.txt" and will consist of:
*		The sorting algorithm being run
*		Every 1000th element of the sorted array
*		The time it took to complete the sort
*
*	An example of the game play output is as follows:
*      BubbleSort:
*		0: 0
*	 1000: 563
*	...
*		SORT TIME: 0.02 seconds
************************************************************/
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <fstream>
#include "Sorts.h"
using std::cout;
using std::cin;
using std::endl;

void main(int argc, char *argv[])
{
	int array_size = 0;

	if (argc < 2)
	{
		cout << "Must pass in an integer to run this program." << endl;
	}
	else
	{
		array_size = atoi(argv[1]);
	
		ofstream file;
		file.open("Sorts.txt");

		Sorts newSort(file, array_size);
		newSort.runSorts();
		newSort.~Sorts();

		file.close();
	}

    #ifdef _WIN32
	if (_CrtDumpMemoryLeaks()) {
		cout << "Memory leaks!" << endl;
	}
	#endif

	return;
}
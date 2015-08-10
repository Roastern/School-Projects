/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 2
* Filename:			Sorts.h
* Date Created:		4/20/2014
* Modifications:	
*
************************************************************/

#ifndef SORTS_H_
#define SORTS_H_

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Array.h"
#include <vector>
#include "BubbleSort.h"
#include "FlagBubble.h"
#include "Selection.h"
#include "Insertion.h"
#include "HeapSort.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "Shell.h"
using std::srand;
using std::rand;
using std::cout;
using std::cin;
using std::endl;

/************************************************************************
* Class: Array
*
* Purpose: This class creates a dynamic one-dimensional array that can be 
*			started at any start index, or resized at any time
*
* Manager functions:	
* 	Sorts (ostream& out_stream, int array_size )
* 		Sets the size of the arrays to be array_size and output stream
*			to out_stream. Sets c-arrays, vectors and Arrays to random values
*	~Sorts ( )
*		deletes the array
*
* Methods:		
*	initiateArray ( )
*		Sets the arrays to be sorted to the starting, unorganized state
*	runSorts ( ) 
*		Runs the arrays through all the sorting algorithms
*	Bubble ( )
*		Runs bubble sort on the c-array, vector and Array
*	FBubble ( )
*		Runs the flagged bubble sort on the c-array, vector and Array
*	Insert ( )
*		Runs the insertion sort on the c-array, vector and Array
*	Select ( )
*		Runs the selection sort on the c-array, vector and Array
*	Shell ( )
*		Runs the shell sort on the c-array, vector and Array
*	Heap ( )
*		Runs the heap sort on the c-array, vector and Array
*	Merg ( )
*		Runs the merge sort on the c-array, vector and Array
*	Quick ( )
*		Runs the quick sort on the c-array, vector and Array
*	clockStart ( )
*		Stores the time used to calculate performance time 
*			for the various sorts
*	stopClock ( )
*		Calculates the time it took for the sort to run
*
*************************************************************************/
class Sorts
{
public:
	Sorts(ostream & out_stream, int size);
	~Sorts();

	void initiateArrays();
	void runSorts();

	void Bubble();
	void FBubble();
	void Insert();
	void Select();
	void Shell();
	void Heap();
	void Merg();
	void Quick();

private:
	clock_t start;
	double sort_time;
	int array_size;
	int * i_array;
	int * i_array_c;
	Array<int> a_array;
	Array<int> a_array_c;
	vector<int> v_array;
	vector<int> v_array_c;
	ostream & out;

	void startClock();
	void stopClock();
};
	


#endif
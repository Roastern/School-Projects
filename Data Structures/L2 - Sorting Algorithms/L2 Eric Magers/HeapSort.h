/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 2
* Filename:			Selection.cpp
* Date Created:		4/16/2014	
* Modifications:	4/19/2014 - moved implementation to 
*								HeapSort.cpp
*					4/20/2014 - added documentation
*
************************************************************/
#ifndef HEAPSORT_H_
#define HEAPSORT_H_

#include <vector>
#include "Array.h"


/**********************************************************************	
* Purpose: Builds a heap out of the given c-array
*
* Entry: m_array is the array to be sorted, f_index is the first 
*			index of the array, l_index is the last
*
* Exit: m_array is sorted into a heap
*		No values are returned
*
************************************************************************/
void MoveDown(int m_array[], int f_index, int l_index);
/**********************************************************************	
* Purpose: Builds a heap out of the given Array
*
* Entry: m_array is the Array to be sorted, f_index is the first 
*			index of the array, l_index is the last
*
* Exit: m_array is sorted into a heap
*		No values are returned
*
************************************************************************/
void MoveDown(Array<int> & m_array, int f_index, int l_index);
/**********************************************************************	
* Purpose: Builds a heap out of the given vector
*
* Entry: m_array is the vector to be sorted, f_index is the first 
*			index of the vector, l_index is the last
*
* Exit: m_array is sorted into a heap
*		No values are returned
*
************************************************************************/
void MoveDown(vector<int> & m_array, int f_index, int l_index);
/**********************************************************************	
* Purpose: Performs the selection sort on the given c-array
*
* Entry: m_array is the array to be sorted, array_size is the size of 
*			the array
*
* Exit: Calls MoveDown() to build the heap
*		m_array is sorted
*		No values are returned
*
************************************************************************/
void HeapSort(int m_array[], int array_size);
/**********************************************************************	
* Purpose: Performs the selection sort on the given Array
*
* Entry: m_array is the array to be sorted, array_size is the size of 
*			the array
*
* Exit: Calls MoveDown() to build the heap
*		m_array is sorted
*		No values are returned
*
************************************************************************/
void HeapSort(Array<int> & m_array, int array_size);
/**********************************************************************	
* Purpose: Performs the selection sort on the given vector
*
* Entry: m_array is the vector to be sorted, array_size is the size of 
*			the array
*
* Exit: Calls MoveDown() to build the heap
*		m_array is sorted
*		No values are returned
*
************************************************************************/
void HeapSort(vector<int> & m_array, int array_size);

#endif
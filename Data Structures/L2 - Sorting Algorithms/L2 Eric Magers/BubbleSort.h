/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 2
* Filename:			BubbleSort.h
* Date Created:		4/10/2014	
* Modifications:	4/19/2014 - moved implementation to 
*								BubbleSort.cpp
*					4/20/2014 - added documentation
*
************************************************************/

#ifndef BUBBLESORT_H_
#define BUBBLESORT_H_

#include "Array.h"
#include <vector>

/**********************************************************************	
* Purpose: Performs the bubble sort on the given c-array,
*			the swapping of elements is done in the swap() function
*
* Entry: m_array is the array to be sorted, m_length is the size of 
*			the array
*
* Exit: No values are returned, m_array is sorted
*
************************************************************************/
void BubbleSortS(int m_array[], int m_length);
/**********************************************************************	
* Purpose: Performs the bubble sort on the given c-array,
*			the swapping of elements is inside the sort
*
* Entry: m_array is the array to be sorted, m_length is the size of 
*			the array
*
* Exit: No values are returned, m_array is sorted
*
************************************************************************/
void BubbleSort(int m_array[], int m_length);
/**********************************************************************	
* Purpose: Performs the bubble sort on the given Array,
*			the swapping of elements is done in the swap() function
*
* Entry: m_array is the array to be sorted
*
* Exit: No values are returned, m_array is sorted
*
************************************************************************/
void BubbleSortS(Array<int> & m_array);
/**********************************************************************	
* Purpose: Performs the bubble sort on the given Array,
*			the swapping of elements is done within the sort
*
* Entry: m_array is the array to be sorted
*
* Exit: No values are returned, m_array is sorted
*
************************************************************************/
void BubbleSort(Array<int> & m_array);
/**********************************************************************	
* Purpose: Performs the bubble sort on the given vector,
*			the swapping of elements is done in the swap() function
*
* Entry: m_array is the vector to be sorted
*
* Exit: No values are returned, m_array is sorted
*
************************************************************************/
void BubbleSortS(vector<int> & m_array);
/**********************************************************************	
* Purpose: Performs the bubble sort on the given vector,
*			the swapping of elements is done within the sort
*
* Entry: m_array is the vector to be sorted
*
* Exit: No values are returned, m_array is sorted
*
************************************************************************/
void BubbleSort(vector<int> & m_array);
/**********************************************************************	
* Purpose: Swaps the values of two elements within m_array
*
* Entry: & m_array is one of the evalues to be swapped with m_array2
*
* Exit: No values are returned, the values stored at the given addresses
*			have been swapped
*
************************************************************************/
void swap(int & m_array, int & m_array2);

#endif
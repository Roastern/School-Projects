/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 2
* Filename:			QuickSort.h
* Date Created:		4/19/2014	
* Modifications:	4/20/2014 - added documentation
*
************************************************************/
#ifndef QUICKSORT_H_
#define QUICKSORT_H_

#include <vector>
#include "Array.h"

/**********************************************************************	
* Purpose: Performs the quick sort on the given c-array
*
* Entry: m_array is the array to be sorted, array_size is the size of 
*			the array
*
* Exit: Moves the largest value stored in m_array to the end of the
*			array. 
*		Calls QuickSort() to sort the remainder of the array
*		m_array is sorted
*		No values are returned
*
************************************************************************/
void QuickSort(int m_array[], int array_size);
/**********************************************************************	
* Purpose: Recursively sorts m_array
*
* Entry: m_array is the array to be sorted, first is the index of the
*			beginning of the portion of the array to be evaluated and
*			last is the last index of that portion
*
* Exit: Calls QuickSort() to sort the remainder of the array
*		No values are returned
*
************************************************************************/
void QuickSort(int m_array[], int first, int last);
/**********************************************************************	
* Purpose: Performs the quick sort on the given Array
*
* Entry: m_array is the array to be sorted, array_size is the size of 
*			the array
*
* Exit: Moves the largest value stored in m_array to the end of the
*			array. 
*		Calls QuickSort() to sort the remainder of the array
*		m_array is sorted
*		No values are returned
*
************************************************************************/
void QuickSort(Array<int> & m_array, int array_size);
/**********************************************************************	
* Purpose: Recursively sorts m_array
*
* Entry: m_array is the array to be sorted, first is the index of the
*			beginning of the portion of the array to be evaluated and
*			last is the last index of that portion
*
* Exit: Calls QuickSort() to sort the remainder of the array
*		No values are returned
*
************************************************************************/
void QuickSort(Array<int> & m_array, int first, int last);
/**********************************************************************	
* Purpose: Performs the quick sort on the given vector
*
* Entry: m_array is the vector to be sorted, array_size is the size of 
*			the vector
*
* Exit: Moves the largest value stored in m_array to the end of the
*			array. 
*		Calls QuickSort() to sort the remainder of the array
*		m_array is sorted
*		No values are returned
*
************************************************************************/
void QuickSort(vector<int> & m_array, int array_size);
/**********************************************************************	
* Purpose: Recursively sorts m_array
*
* Entry: m_array is the array to be sorted, first is the index of the
*			beginning of the portion of the array to be evaluated and
*			last is the last index of that portion
*
* Exit: Calls QuickSort() to sort the remainder of the array
*		No values are returned
*
************************************************************************/
void QuickSort(vector<int> & m_array, int first, int last);

#endif
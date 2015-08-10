/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 2
* Filename:			MergeSort.h
* Date Created:		4/10/2014
* Modifications:	4/19/2014 - moved implementation to 
*								MergeSort.cpp
*					4/20/2014 - Added documentation
*
************************************************************/

#ifndef MERGESORT_H_
#define MERGESORT_H_

#include <vector>
#include "Array.h"

/**********************************************************************	
* Purpose: Sorts the given sections of m_array and stored the values
*			in the appropriate places in temp_array, then copies
*			temp_array into m_array
*
* Entry: m_array is the array to be sorted, temp_array is the array to
*			store the sorted portions of m_array, left is the left
*			most index of m_array to be evaluated, right is the
*			middle index and l_right most index to be evaluated
*
* Exit: The given portion of m_array is sorted and stored in the 
*			appropriate position within m_array
*
************************************************************************/
void Merge(int m_array[], int temp_array[], int left, int right, int l_right);
/**********************************************************************	
* Purpose: Recursively breaks m_array into smaller parts to be sorted
*			and stored within temp_array
*
* Entry: m_array is the array to be sorted, temp_array is the array to
*			store the sorted portions of m_array, left is the left
*			most index of m_array to be evaluated, right is the
*			right most index to be evaluated
*
* Exit: Splits m_array into two portions, and passes each portion 
*			recursively to itself until each portion is of length 1
*		Calls Merge() to sort and combine each section
*
************************************************************************/
void MergeSort(int m_array[], int temp_array[], int left, int right);
/**********************************************************************	
* Purpose: Performs the merge sort on the given c-array
*
* Entry: m_array is the c-array to be sorted, array_size is the size
*			of m_array
*
* Exit: Creates temporary array of the same size as m_array. 
*		Passes m_array, temp_array, 0 and array_size to MergeSort to be
*			sorted
*
************************************************************************/
void MergeSort(int m_array[], int array_size);

/**********************************************************************	
* Purpose: Sorts the given sections of m_array and stored the values
*			in the appropriate places in temp_array, then copies
*			temp_array into m_array
*
* Entry: m_array is the array to be sorted, temp_array is the array to
*			store the sorted portions of m_array, left is the left
*			most index of m_array to be evaluated, right is the
*			middle index and l_right most index to be evaluated
*
* Exit: The given portion of m_array is sorted and stored in the 
*			appropriate position within m_array
*
************************************************************************/
void Merge(Array<int> & m_array, Array<int> & temp_array, int left, int right, int l_right);
/**********************************************************************	
* Purpose: Recursively breaks m_array into smaller parts to be sorted
*			and stored within temp_array
*
* Entry: m_array is the array to be sorted, temp_array is the array to
*			store the sorted portions of m_array, left is the left
*			most index of m_array to be evaluated, right is the
*			right most index to be evaluated
*
* Exit: Splits m_array into two portions, and passes each portion 
*			recursively to itself until each portion is of length 1
*		Calls Merge() to sort and combine each section
*
************************************************************************/
void MergeSort(Array<int> & m_array, Array<int> & temp_array, int left, int right);
/**********************************************************************	
* Purpose: Performs the merge sort on the given Array
*
* Entry: m_array is the c-array to be sorted, array_size is the size
*			of m_array
*
* Exit: Creates temporary array of the same size as m_array. 
*		Passes m_array, temp_array, 0 and array_size to MergeSort to be
*			sorted
*
************************************************************************/
void MergeSort(Array<int> & m_array, int array_size);

/**********************************************************************	
* Purpose: Sorts the given sections of m_array and stored the values
*			in the appropriate places in temp_array, then copies
*			temp_array into m_array
*
* Entry: m_array is the array to be sorted, temp_array is the array to
*			store the sorted portions of m_array, left is the left
*			most index of m_array to be evaluated, right is the
*			middle index and l_right most index to be evaluated
*
* Exit: The given portion of m_array is sorted and stored in the 
*			appropriate position within m_array
*
************************************************************************/
void Merge(vector<int> & m_array, vector<int> & temp_array, int left, int right, int l_right);
/**********************************************************************	
* Purpose: Recursively breaks m_array into smaller parts to be sorted
*			and stored within temp_array
*
* Entry: m_array is the array to be sorted, temp_array is the array to
*			store the sorted portions of m_array, left is the left
*			most index of m_array to be evaluated, right is the
*			right most index to be evaluated
*
* Exit: Splits m_array into two portions, and passes each portion 
*			recursively to itself until each portion is of length 1
*		Calls Merge() to sort and combine each section
*
************************************************************************/
void MergeSort(vector<int> & m_array, vector<int> & temp_array, int left, int right);
/**********************************************************************	
* Purpose: Performs the merge sort on the given vector
*
* Entry: m_array is the c-array to be sorted, array_size is the size
*			of m_array
*
* Exit: Creates temporary array of the same size as m_array. 
*		Passes m_array, temp_array, 0 and array_size to MergeSort to be
*			sorted
*
************************************************************************/
void MergeSort(vector<int> & m_array, int array_size);

#endif
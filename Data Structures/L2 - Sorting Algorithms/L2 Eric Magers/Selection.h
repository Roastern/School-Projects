/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 2
* Filename:			Selection.h
* Date Created:		4/10/2014	
* Modifications:	4/19/2014 - moved implementation to 
*								Selection.cpp
*					4/20/2014 - added documentation
*
************************************************************/

#ifndef SELECTION_H_
#define SELECTION_H_

#include "Array.h"
#include <vector>

/**********************************************************************	
* Purpose: Performs the selection sort on the given c-array
*
* Entry: m_array is the array to be sorted, m_length is the size of 
*			the array
*
* Exit: No values are returned, m_array is sorted
*
************************************************************************/
void Selection(int m_array[], int m_length);
/**********************************************************************	
* Purpose: Performs the selection sort on the given Array
*
* Entry: m_array is the array to be sorted
*
* Exit: No values are returned, m_array is sorted
*
************************************************************************/
void Selection(Array<int> & m_array);
/**********************************************************************	
* Purpose: Performs the selection sort on the given vector
*
* Entry: m_array is the vector to be sorted
*
* Exit: No values are returned, m_array is sorted
*
************************************************************************/
void Selection(vector<int> & m_array);
/**********************************************************************	
* Purpose: Swaps the values of two elements within m_array
*
* Entry: & m_array is one of the evalues to be swapped with m_array2
*
* Exit: No values are returned, the values stored at the given addresses
*			have been swapped
*
************************************************************************/
void selswap(int & m_array, int & m_array2);

#endif
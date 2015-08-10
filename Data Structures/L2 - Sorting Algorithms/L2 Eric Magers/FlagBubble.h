/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 2
* Filename:			FlagBubble.h
* Date Created:		4/10/2014	
* Modifications:	4/19/2014 - moved implementation to 
*								FlagBubble.cpp
*					4/20/2014 - added documentation
*
************************************************************/

#ifndef FLAGBUBBLE_H_
#define FLAGBUBBLE_H_

#include <vector>
#include "Array.h"

/**********************************************************************	
* Purpose: Performs the flagged bubble sort on the given c-array,
*
* Entry: m_array is the array to be sorted, m_length is the size of 
*			the array
*
* Exit: No values are returned, m_array is sorted
*
************************************************************************/
void FlagBubble(int m_array[], int m_length);
/**********************************************************************	
* Purpose: Performs the flagged bubble sort on the given Array,
*
* Entry: m_array is the array to be sorted
*
* Exit: No values are returned, m_array is sorted
*
************************************************************************/
void FlagBubble(Array<int> & m_array);
/**********************************************************************	
* Purpose: Performs the flagged bubble sort on the given vector,
*
* Entry: m_array is the vector to be sorted
*
* Exit: No values are returned, m_array is sorted
*
************************************************************************/
void FlagBubble(vector<int> & m_array);

#endif
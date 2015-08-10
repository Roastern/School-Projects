/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 2
* Filename:			FlagBubble.cpp
* Date Created:		4/19/2014	
* Modifications:	
*
************************************************************/
#include "FlagBubble.h"

void FlagBubble(int m_array[], int m_length)
{
	bool sorted = true;
	for (int i = 0; (i < m_length) && sorted; i++)
	{
		sorted = false;
		for (int n = 0; n < m_length - 1 - i; n++)
		{
			if (m_array[n] > m_array[n + 1])
			{      
				int temp = m_array[n];
				m_array[n] = m_array[n+1];
				m_array[n+1] = temp;
				sorted = true;
			}
		}
	}
}

void FlagBubble(Array<int> & m_array)
{
	int m_length = m_array.getLength();
	bool sorted = true;

	for (int i = 0; (i < m_length) && sorted; i++)
	{
		sorted = false;
		for (int n = 0; n < m_length - 1; n++)
		{
			if (m_array[n] > m_array[n + 1])
			{    
				int temp = m_array[n];
				m_array[n] = m_array[n+1];
				m_array[n + 1] = temp;
				sorted = true;
			}
		}
	}
}

void FlagBubble(vector<int> & m_array)
{
	int m_length = m_array.size();
	bool sorted = true;

	for (int i = 0; (i < m_length) && sorted; i++)
	{
		sorted = false;
		for (int n = 0; n < m_length - 1; n++)
		{
			if (m_array[n] > m_array[n + 1])
			{  
				int temp = m_array[n];
				m_array[n] = m_array[n + 1];
				m_array[n + 1] = temp;
				sorted = true;
			}
		}
	}
}
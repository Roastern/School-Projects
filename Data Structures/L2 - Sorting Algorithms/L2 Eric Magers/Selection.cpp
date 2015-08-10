/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 2
* Filename:			Selection.cpp
* Date Created:		4/19/2014	
* Modifications:	
*
************************************************************/

#include "Selection.h"

void Selection(int m_array[], int m_length)
{
	int s_loop;
	int max;

	for (int i = m_length - 1; i > 0; i--)
	{
		for (s_loop = 1, max = 0; s_loop < i; s_loop++)
		{
			if (m_array[s_loop] > m_array[max])
			{
				max = s_loop;
			}
		}
		selswap(m_array[s_loop], m_array[max]);
	}
}

void Selection(Array<int> & m_array)
{
	int m_length = m_array.getLength();
	int s_loop;
	int max;

	for (int i = m_length - 1; i > 0; i--)
	{
		for (s_loop = 1, max = 0; s_loop < i; s_loop++)
		{
			if (m_array[s_loop] > m_array[max])
			{
				max = s_loop;
			}
		}
		selswap(m_array[s_loop], m_array[max]);
	}
}

void Selection(vector<int> & m_array)
{
	int m_length = m_array.size();
	int s_loop;
	int max;

	for (int i = m_length - 1; i > 0; i--)
	{
		for (s_loop = 1, max = 0; s_loop < i; s_loop++)
		{
			if (m_array[s_loop] > m_array[max])
			{
				max = s_loop;
			}
		}
		selswap(m_array[s_loop], m_array[max]);
	}
}

void selswap(int & m_array, int & m_array2)
{
	int temp = m_array;
	m_array = m_array2;
	m_array2 = temp;
}

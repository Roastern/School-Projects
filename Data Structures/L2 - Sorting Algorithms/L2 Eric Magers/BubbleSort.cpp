/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 2
* Filename:			BubbleSort.cpp
* Date Created:		4/19/2014	
* Modifications:	
*
************************************************************/

#include "BubbleSort.h"

void BubbleSort(int m_array[], int m_length)
{
	for (int i = 0; i < m_length; i++)
	{
		for (int n = 0; n < m_length - 1; n++)
		{
			if (m_array[n] > m_array[n + 1])
			{  
				int temp = m_array[n];
				m_array[n] = m_array[n+1];
				m_array[n + 1] = temp;
			}
		}
	}
}

void BubbleSort(Array<int> & m_array)
{
	int m_length = m_array.getLength();

	for (int i = 0; i < m_length; i++)
	{
		for (int n = 0; n < m_length - 1; n++)
		{
			if (m_array[n] > m_array[n + 1])
			{ 
				int temp = m_array[n];
				m_array[n] = m_array[n+1];
				m_array[n + 1] = temp;
			}
		}
	}
}

void BubbleSort(vector<int> & m_array)
{
	int m_length = m_array.size();

	for (int i = 0; i < m_length; i++)
	{
		for (int n = 0; n < m_length - 1; n++)
		{
			if (m_array[n] > m_array[n + 1])
			{   
				int temp = m_array[n];
				m_array[n] = m_array[n + 1];
				m_array[n + 1] = temp;
			}
		}
	}
}

void BubbleSortS(int m_array[], int m_length)
{
	for (int i = 0; i < m_length; i++)
	{
		for (int n = 0; n < m_length - 1; n++)
		{
			if (m_array[n] > m_array[n + 1])
			{
				swap(m_array[n], m_array[n + 1]);   
			}
		}
	}
}

void BubbleSortS(Array<int> & m_array)
{
	int m_length = m_array.getLength();

	for (int i = 0; i < m_length; i++)
	{
		for (int n = 0; n < m_length - 1; n++)
		{
			if (m_array[n] > m_array[n + 1])
			{
				swap(m_array[n], m_array[n + 1]);   
			}
		}
	}
}

void BubbleSortS(vector<int> & m_array)
{
	int m_length = m_array.size();

	for (int i = 0; i < m_length; i++)
	{
		for (int n = 0; n < m_length - 1; n++)
		{
			if (m_array[n] > m_array[n + 1])
			{
				swap(m_array[n], m_array[n + 1]);   
			}
		}
	}
}
void swap(int & m_array, int & m_array2)
{
	int temp = m_array;
	m_array = m_array2;
	m_array2 = temp;
}
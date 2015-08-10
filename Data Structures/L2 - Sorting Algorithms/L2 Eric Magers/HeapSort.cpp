/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 2
* Filename:			Selection.cpp
* Date Created:		4/19/2014	
* Modifications:	
*
************************************************************/
#include "HeapSort.h"

void MoveDown(int m_array[], int f_index, int l_index)
{
	int largest = f_index * 2 + 1;
	int temp;

	while (largest <= l_index)
	{
		if (largest < l_index && (m_array[largest] < m_array[f_index] || m_array[largest] < m_array[largest + 1]))
		{
			largest++;
		}

		if (m_array[f_index] < m_array[largest])
		{
			temp = m_array[f_index];
			m_array[f_index] = m_array[largest];
			m_array[largest] = temp;

			f_index = largest;
			largest = f_index * 2 + 1;
		}
		else
			largest = l_index + 1;
	}
}

void MoveDown(Array<int> & m_array, int f_index, int l_index)
{
	int largest = f_index * 2 + 1;
	int temp;

	while (largest <= l_index)
	{
		if (largest < l_index && (m_array[largest] < m_array[f_index] || m_array[largest] < m_array[largest + 1]))
		{
			largest++;
		}

		if (m_array[f_index] < m_array[largest])
		{
			temp = m_array[f_index];
			m_array[f_index] = m_array[largest];
			m_array[largest] = temp;

			f_index = largest;
			largest = f_index * 2 + 1;
		}
		else
			largest = l_index + 1;
	}
}

void MoveDown(vector<int> & m_array, int f_index, int l_index)
{
	int largest = f_index * 2 + 1;
	int temp;

	while (largest <= l_index)
	{
		if (largest < l_index && (m_array[largest] < m_array[f_index] || m_array[largest] < m_array[largest + 1]))
		{
			largest++;
		}

		if (m_array[f_index] < m_array[largest])
		{
			temp = m_array[f_index];
			m_array[f_index] = m_array[largest];
			m_array[largest] = temp;

			f_index = largest;
			largest = f_index * 2 + 1;
		}
		else
			largest = l_index + 1;
	}
}

void HeapSort(int m_array[], int array_size)
{
	int temp;
	for (int i = (array_size/2); i >= 0; i--)
	{
		MoveDown(m_array, i, array_size - 1);
	}

	for (int i = (array_size - 1); i >= 0; i--)
	{
		temp = m_array[i];
		m_array[i] = m_array[0];
		m_array[0] = temp;

		MoveDown(m_array, 0, i - 1);
	}
}

void HeapSort(Array<int> & m_array, int array_size)
{
	int temp;
	for (int i = (array_size/2); i >= 0; i--)
	{
		MoveDown(m_array, i, array_size - 1);
	}

	for (int i = (array_size - 1); i >= 0; i--)
	{
		temp = m_array[i];
		m_array[i] = m_array[0];
		m_array[0] = temp;

		MoveDown(m_array, 0, i - 1);
	}
}

void HeapSort(vector<int> & m_array, int array_size)
{
	int temp;
	for (int i = (array_size/2); i >= 0; i--)
	{
		MoveDown(m_array, i, array_size - 1);
	}

	for (int i = (array_size - 1); i >= 0; i--)
	{
		temp = m_array[i];
		m_array[i] = m_array[0];
		m_array[0] = temp;

		MoveDown(m_array, 0, i - 1);
	}
}
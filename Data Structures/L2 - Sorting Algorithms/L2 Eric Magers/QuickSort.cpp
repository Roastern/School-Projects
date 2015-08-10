/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 2
* Filename:			QuickSort.cpp
* Date Created:		4/19/2014	
* Modifications:	
*
************************************************************/
#include "QuickSort.h"

void QuickSort(int m_array[], int array_size)
{
	int max = 0;
	int temp;

	if (array_size >= 2)
	{
		for (int i = 1; i < array_size; i++)
		{
			if (m_array[max] < m_array[i])
			{
				max = i;
			}
		}

		temp = m_array[max];
		m_array[max] = m_array[array_size - 1];
		m_array[array_size - 1] = temp;

		QuickSort(m_array, 0, array_size - 2);
	}
}

void QuickSort(int m_array[], int first, int last)
{
	int small = first + 1;
	int large = last;
	int pivot = m_array[first];

	while (small <= large)
	{
		while (m_array[small] < pivot)
			small++;
		while (m_array[large] > pivot)
			large--;
		
		if (small < large)
		{
			swap(m_array[small++], m_array[large--]);
		}
		else
			small++;
	}

	swap(m_array[first], m_array[large]);

	if (first < large - 1)
		QuickSort(m_array, first, large - 1);
	if (last > large + 1)
		QuickSort(m_array, large + 1, last);
}

void QuickSort(Array<int> & m_array, int array_size)
{
	int max = 0;
	int temp;

	if (array_size >= 2)
	{
		for (int i = 1; i < array_size; i++)
		{
			if (m_array[max] < m_array[i])
			{
				max = i;
			}
		}

		temp = m_array[max];
		m_array[max] = m_array[array_size - 1];
		m_array[array_size - 1] = temp;

		QuickSort(m_array, 0, array_size - 2);
	}
}

void QuickSort(Array<int> & m_array, int first, int last)
{
	int small = first + 1;
	int large = last;
	int pivot = m_array[first];

	while (small <= large)
	{
		while (m_array[small] < pivot)
			small++;
		while (m_array[large] > pivot)
			large--;
		
		if (small < large)
		{
			swap(m_array[small++], m_array[large--]);
		}
		else
			small++;
	}

	swap(m_array[first], m_array[large]);

	if (first < large - 1)
		QuickSort(m_array, first, large - 1);
	if (last > large + 1)
		QuickSort(m_array, large + 1, last);
}

void QuickSort(vector<int> & m_array, int array_size)
{
	int max = 0;
	int temp;

	if (array_size >= 2)
	{
		for (int i = 1; i < array_size; i++)
		{
			if (m_array[max] < m_array[i])
			{
				max = i;
			}
		}

		temp = m_array[max];
		m_array[max] = m_array[array_size - 1];
		m_array[array_size - 1] = temp;

		QuickSort(m_array, 0, array_size - 2);
	}
}

void QuickSort(vector<int> & m_array, int first, int last)
{
	int small = first + 1;
	int large = last;
	int pivot = m_array[first];

	while (small <= large)
	{
		while (m_array[small] < pivot)
			small++;
		while (m_array[large] > pivot)
			large--;
		
		if (small < large)
		{
			swap(m_array[small++], m_array[large--]);
		}
		else
			small++;
	}

	swap(m_array[first], m_array[large]);

	if (first < large - 1)
		QuickSort(m_array, first, large - 1);
	if (last > large + 1)
		QuickSort(m_array, large + 1, last);
}
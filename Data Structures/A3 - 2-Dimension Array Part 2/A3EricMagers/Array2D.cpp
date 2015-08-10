/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Assignment 2
* Filename:			Row.h
* Date Created:		4/2/2014
* Modifications:	4/3/2014 – Added documentation
************************************************************/
#ifndef ARRAY2D_CPP_
#define ARRAY2D_CPP_

#include "Array2D.h"
#include "Row.cpp"
#include "Exception.h"
#include <iostream>
using namespace std;

template<typename T>
Array2D<T>::Array2D() : m_array(nullptr), m_row(0), m_col(0)
{
	
}

template<typename T>
Array2D<T>::Array2D(int row, int col) : m_row(row), m_col(col)
{
	m_array = new T*[m_row];

	for (int i = 0; i < m_row; i++)
	{
		m_array[i] = new T[m_col];

		for (int j = 0; j < m_col; j++)
		{
			m_array[i][j] = T();
		}
	}
}

template<typename T>
Array2D<T>::Array2D(const Array2D<T> &copy) : m_row(copy.getRow()), m_col(copy.getColumn())
{
	if (copy.m_array == nullptr)
	{
		m_array = nullptr;
	}
	else
	{
		m_array = new T*[m_row];
	
		for (int i = 0; i < m_row; i++)
		{
			m_array[i] = new T[m_col];

			for (int j = 0; j < m_col; j++)
			{
				m_array[i][j] = copy.m_array[i][j];
			}
		}
	}
}

template<typename T>
Array2D<T>::~Array2D()
{
	for (int i = 0; i < m_row; i++)
	{
		delete [] m_array[i];
		m_array[i] = nullptr;
	}
	delete [] m_array;
	m_array = nullptr;

	m_row = 0;
	m_col = 0;
}

template<typename T>
Array2D<T>& Array2D<T>::operator=(const Array2D &rhs)
{
	if (m_array == rhs.m_array)
	{
		return *this;
	}
	else
	{
		if (m_array != nullptr)
		{
			for (int i = 0; i < m_row; i++)
			{
				delete [] m_array[i];
				m_array[i] = nullptr;
			}
			delete [] m_array;
			m_array = nullptr;
		}

		m_row = rhs.getRow();
		m_col = rhs.getColumn();

		m_array = new T*[m_row];

		for (int i = 0; i < m_row; i++)
		{
			m_array[i] = new T[m_col];

			for (int j = 0; j < m_col; j++)
			{
				m_array[i][j] = rhs.m_array[i][j];
			}
		}
	}
	return *this;
}

template<typename T>
Row<T> Array2D<T>::operator [] (int row)
{
	if (row >= m_row)
		throw Exception("Row index exceeds upper bounds");
	else if (row < 0)
		throw Exception("Row index exceeds lower bounds");

	Row<T> find_row(*this, row);
	
	return find_row;
}

template<typename T>
Row<T> Array2D<T>::operator [] (int row) const
{
	if (row >= m_row)
		throw Exception("Row index exceeds upper bounds");
	else if (row < 0)
		throw Exception("Row index exceeds lower bounds");

	const Array2D<T>& here = *this;

	Row<T> find_row(const_cast<Array2D<T>&>(here), row);
	
	return find_row;
}

template<typename T>
int Array2D<T>::getRow() const
{
	return m_row;
}

template<typename T>
void Array2D<T>::setRow(int rows)
{
	if (rows < 0)
	{
		throw Exception("Number of rows must be greater than or equal to 0");
	}

	T** new_array = new T*[rows];

	for (int i = 0; i < rows; i++)
	{
		new_array[i] = new T[m_col];

		for (int j = 0; j < m_col; j++)
		{
			if (i >= m_row)
				new_array[i][j] = T();
			else
				new_array[i][j] = m_array[i][j];
		}
	}

	for (int i = 0; i < m_row; i++)
	{
		delete [] m_array[i];
		m_array[i] = nullptr;
	}
	delete [] m_array;
	m_array = nullptr;

	m_row = rows;
	m_array = new_array;
}

template<typename T>
int Array2D<T>::getColumn() const
{
	return m_col;
}

template<typename T>
void Array2D<T>::setColumn(int columns)
{
	if (columns < 0)
	{
		throw Exception("Number of columns must be greater than or equal to 0");
	}

	if (m_array == nullptr)
	{
		m_col = columns;
		m_array = new T*[m_row];

		for (int i = 0; i < m_row; i++)
		{
			m_array[i] = new T[m_col];

			for (int j = 0; j < m_col; j++)
			{
				m_array[i][j] = T();
			}
		}
	}
	else
	{
		T** new_array = new T*[m_row];

		for (int i = 0; i < m_row; i++)
		{
			new_array[i] = new T[columns];

			for (int j = 0; j < columns; j++)
			{
				if (j >= m_col)
				{
					new_array[i][j] = T();
				}
				else
					new_array[i][j] = m_array[i][j];
			}
		}

		for (int i = 0; i < m_row; i++)
		{
			delete [] m_array[i];
			m_array[i] = nullptr;
		}
		delete [] m_array;
		
		m_col = columns;
		m_array = new_array;
	}
}

template<typename T>
T& Array2D<T>::Select(int row, int column)
{
	return m_array[row][column];
}

#endif
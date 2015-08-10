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
#include "Array.cpp"
#include "Row.cpp"
#include "Exception.h"
#include <iostream>

template<typename T>
Array2D<T>::Array2D() : m_array(), m_row(0), m_col(0)
{

}

template<typename T>
Array2D<T>::Array2D(int row, int col) : m_array(0), m_row(row), m_col(col)
{
	m_array.setLength(m_row * m_col);
}

template<typename T>
Array2D<T>::Array2D(const Array2D<T> &copy) : m_array(copy.getRow() * copy.getColumn()), m_row(copy.getRow()), m_col(copy.getColumn())
{
	m_array = copy.m_array;
}

template<typename T>
Array2D<T>::~Array2D()
{
	
}

template<typename T>
Array2D<T>& Array2D<T>::operator=(const Array2D &rhs)
{
	this->setRow(rhs.getRow());
	this->setColumn(rhs.getColumn());
	this->m_array = rhs.m_array;

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
	m_row = rows;
	m_array.setLength(m_row * m_col);
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

	if (m_array.getLength() == 0)
	{
		m_col = columns;
		m_array.setLength(m_row * m_col);
	}
	else
	{
		Array<T> copy_array(m_row * columns);

		for (int i = 0; i < m_row; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				if ((((i * columns) + j) - (i * (columns - m_col))) < ((i * m_col) + m_col))
				{
					copy_array[(i * columns) + j] = m_array[(i * m_col) + j];
				}
			}
		}
		m_col = columns;
		m_array = copy_array;
	}
}

template<typename T>
T& Array2D<T>::Select(int row, int column)
{
	return m_array[(row * m_col) + column];
}

#endif
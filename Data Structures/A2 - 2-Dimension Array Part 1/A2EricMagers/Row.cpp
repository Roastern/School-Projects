/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Assignment 2
* Filename:			Row.cpp
* Date Created:		4/2/2014
* Modifications:	4/3/2014 – Added documentation
************************************************************/
#ifndef ROW_CPP_
#define ROW_CPP_

#include "Row.h"
#include "Exception.h"

template<typename T>
Row<T>::Row(Array2D<T> &array, int row) : m_array2D(array), m_row(row)
{
	
}

template<typename T>
T& Row<T>::operator [] (int column)
{
	if (column >= m_array2D.getColumn())
	{
		throw Exception("Column exceeds upper bounds");
	}
	else if (column < 0)
	{
		throw Exception("Column exceeds lower bounds");
	}

	return m_array2D.Select(m_row, column);
}

template<typename T>
T& Row<T>::operator [] (int column) const
{
	if (column >= m_array2D.getColumn())
	{
		throw Exception("Column exceeds upper bounds");
	}
	else if (column < 0)
	{
		throw Exception("Column exceeds lower bounds");
	}

	return m_array2D.Select(m_row, column);
}

#endif
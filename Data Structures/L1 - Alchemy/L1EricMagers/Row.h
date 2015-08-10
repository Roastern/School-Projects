/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Assignment 2
* Filename:			Row.h
* Date Created:		4/2/2014
* Modifications:	4/3/2014 – Added documentation
************************************************************/
#ifndef ROW_H_
#define ROW_H_

#include "Exception.h"

template<typename T>
class Array2D;

/************************************************************************
* Class: Row
*
* Purpose: This class returns the value stored in the Array2D object
*			specified by the given row and column.
*
* Manager functions:	
* 	Row (Array2D &array, int row)
* 		Initializes the address of Row's array to that of the given array,
*			and Row's m_row to the given row.
*
* Methods:		
*	operator [ ] (int column)
*		Returns the value within the array at the specified column within
*			the given row.
*************************************************************************/
template<typename T>
class Row
{
public:
	Row(Array2D<T> &array, int row);

	T& operator [] (int column);
	T& operator [] (int column) const;

private:
	Array2D<T>& m_array2D;
	int m_row;
};

/**********************************************************************	
* Purpose: Default constructor, sets m_array2D and m_row to the given
*			values
*
* Entry: array is the address of the Array2D object to be stored in m_array2D
*			and m_row is the value to be stored in m_row
*
* Exit: Nothing is returned
*		m_array2D and m_row are initialized to the appropriate values
*
************************************************************************/
template<typename T>
Row<T>::Row(Array2D<T> &array, int row) : m_array2D(array), m_row(row)
{
	
}

/**********************************************************************	
* Purpose: Returns the data stored at the specified column of m_array2D
*			in the row m_row
*
* Entry: column is the column index used to find the queried data
*			column must be greater than or equal to 0 and less than
*			m_array2D's m_col
*
* Exit: Calls Select(), a member function of m_array2D to get the value
*			stored at m_array2D[row][column]
*		Returns the value which was returned by Select()
*
************************************************************************/
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

/**********************************************************************	
* Purpose: Returns the data stored at the specified column of m_array2D
*			in the row m_row
*
* Entry: column is the column index used to find the queried data
*			column must be greater than or equal to 0 and less than
*			m_array2D's m_col
*
* Exit: Calls Select(), a member function of m_array2D to get the value
*			stored at m_array2D[row][column]
*		Returns the value which was returned by Select() as a constant
*
************************************************************************/
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
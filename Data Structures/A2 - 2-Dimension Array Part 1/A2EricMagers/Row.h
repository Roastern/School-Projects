/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Assignment 2
* Filename:			Row.h
* Date Created:		4/2/2014
* Modifications:	4/3/2014 – Added documentation
************************************************************/
#ifndef ROW_H_
#define ROW_H_

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

#endif
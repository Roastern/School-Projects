/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Assignment 2
* Filename:			Row.h
* Date Created:		4/2/2014
* Modifications:	4/3/2014 – Added documentation
************************************************************/
#ifndef ARRAY2D_H_
#define ARRAY2D_H_

#include "Array.cpp"
#include "Row.h"


/************************************************************************
* Class: Array2D
*
* Purpose: This class stores an Array object and accesses it with a 2D
*			array style of functionality
*
* Manager functions:	
* 	Array2D ( )
* 		Initializes the Array2D object to default values, the Array is set
*			to a length of 0.
*	Array2D (int row, int col = 0)
*		Initializes the Array2D object to specified values, columns are set
*			to 0 if client does not pass it as an argument. Array's length
*			is set to row * columns
*	Array2D (const Array2D &copy)
*		Initializes the Array2D object to the same size as the copy object,
*			then copies the array into the new object.
*	~Array2D ( )
*		Deletes the Array2D object
*	operator = (const Array2D &rhs)
*		Copies rhs into the specified Array2D object
*
* Methods:		
*	operator [ ] (int column)
*		Returns a Row object to be evaluated by Row's overloaded [ ]
*	operator [ ] (int column) const
*		Returns a Row object with a constant Array2D reference
*	int getRow ( ) const
*		Returns the number of rows in the Array2D object
*	void setRow (int rows) 
*		Sets the number of rows in the Array2D object
*	int getColumn ( ) const
*		Returns the number of columns in the Array2D object
*	void setColumn ( ) 
*		Sets the number of columns in the Array2D object
*	Select (int row, int column)
*		Returns the value stored in the Array at the index row * column
*************************************************************************/
template<typename T>
class Array2D
{
public:
	Array2D();
	Array2D(int row, int col = 0);
	Array2D(const Array2D<T> &copy);
	~Array2D();

	Array2D<T>& operator=(const Array2D<T> &rhs);
	Row<T> operator[](int index);
	Row<T> operator[](int index) const;

	int getRow() const;
	void setRow(int rows);
	int getColumn() const;
	void setColumn(int columns);

	T& Select(int row, int column);

private:
	Array<T> m_array;
	int m_row;
	int m_col;
};

#endif
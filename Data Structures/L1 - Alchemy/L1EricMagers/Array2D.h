/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Assignment 2
* Filename:			Row.h
* Date Created:		4/2/2014
* Modifications:	4/3/2014 – Added documentation
*					4/8/2014 - Added function documentation
*								and moved function declarations
*								to the Array2D.h file
************************************************************/
#ifndef ARRAY2D_H_
#define ARRAY2D_H_

#include "Row.h"
#include "Exception.h"
#include "Array.h"

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

/**********************************************************************	
* Purpose: Default constructor, initializes the m_array to it's default
*			values and initializes m_row and m_col to 0
*
* Entry: No values are entered
*
* Exit: No values are returned
*
************************************************************************/
template<typename T>
Array2D<T>::Array2D() : m_array(), m_row(0), m_col(0)
{

}

/**********************************************************************	
* Purpose: Initializes the m_array to the length of 
*			row * col, and initializes m_row and m_col to the given values
*
* Entry: row is the number of rows in the Array2D object, and col is the
*			number of columns in the Array2D object
*
* Exit: Calls m_array.setLength() to set the length of the Array object
*			to be that of m_row * m_col after initializing these to their
*			given values
*		Does not return any values
*
************************************************************************/
template<typename T>
Array2D<T>::Array2D(int row, int col) : m_array(0), m_row(row), m_col(col)
{
	m_array.setLength(m_row * m_col);
}

/**********************************************************************	
* Purpose: Copies the values stored in the given Array2D object into the
*			new Array2D object
*
* Entry: copy is the Array2D object to be copied
*
* Exit: Initializes m_row to be that of copy.getRow() and m_col to be that
*			of copy.getColumn()
*		Sets m_array to equal copy's m_array
*		Does not return any values
*
************************************************************************/
template<typename T>
Array2D<T>::Array2D(const Array2D<T> &copy) : m_row(copy.getRow()), m_col(copy.getColumn())
{
	m_array = copy.m_array;
}

/**********************************************************************	
* Purpose: Destroys the current Array2D object
*
* Entry: No values are passed to this function
*
* Exit: The Array2D object is destroyed
*		No values are returned
*
************************************************************************/
template<typename T>
Array2D<T>::~Array2D()
{
	
}

/**********************************************************************	
* Purpose: Copies the values in the given Array2D object into the current
*			Array2D object
*
* Entry: rhs is the Array2D object to be copied
*
* Exit: Sets m_row to be that of rhs's m_row
*		Sets m_col to be that of rhs's m_col
*		Sets m_array to be that of rhs's m_array
*		Returns the address of the current Array2D object
*
************************************************************************/
template<typename T>
Array2D<T>& Array2D<T>::operator=(const Array2D &rhs)
{
	this->setRow(rhs.getRow());
	this->setColumn(rhs.getColumn());
	this->m_array = rhs.m_array;

	return *this;
}

/**********************************************************************	
* Purpose: Returns a row object which is created using the current 
*			Array2D address and the given row value
*
* Entry: row is the row index for the data the client wishes to access
*		 row must be greater or equal to 0
*		 row must be less than m_row
*
* Exit: Creates the Row object, find_row, with the current Array2D address
*			and the given row value
*		Returns find_row
*
************************************************************************/
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

/**********************************************************************	
* Purpose: Returns a row object which is created using the current 
*			Array2D address and the given row value
*
* Entry: row is the row index for the data the client wishes to access
*		 row must be greater or equal to 0
*		 row must be less than m_row
*
* Exit: Creates the const Row object, find_row, with the current Array2D address
*			and the given row value
*		Returns find_row
*
************************************************************************/
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

/**********************************************************************	
* Purpose: Returns the number of rows in the Array2D object
*
* Entry: No values are passed to this function
*
* Exit: m_row, the number of rows in the object is returned
*
************************************************************************/
template<typename T>
int Array2D<T>::getRow() const
{
	return m_row;
}

/**********************************************************************	
* Purpose: Sets the number of rows of the Array2D object
*
* Entry: rows is the new number of rows for the Array2D object
*		 rows must be greater than 0
*
* Exit: Nothing is returned
*		if rows < m_row, data is lost
*		if rows >= m_row, extra rows are added to the end of m_array and  
*			all data is preserved in the current row/column index positions
*		m_rows is set to rows
*		setLength() is called to change the length of m_array to be that
*			of m_row * m_col
*		
*
************************************************************************/
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

/**********************************************************************	
* Purpose: Returns the number of columns in the Array2D object
*
* Entry: No values are passed to this function
*
* Exit: m_col, the number of columns in the object is returned
*
************************************************************************/
template<typename T>
int Array2D<T>::getColumn() const
{
	return m_col;
}

/**********************************************************************	
* Purpose: Sets the number of columns of the Array2D object
*
* Entry: columns is the new number of columns for the Array2D object
*		 columns must be greater than 0
*
* Exit: Nothing is returned
*		if columns < m_col, all data in the columns which are no longer
*			valid is deleted
*		if columns >= m_col, columns are added at the end of each row 
*			and all data is preserved in the current row/column
*			index positions
*		m_col is set to columns
*
************************************************************************/
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

/**********************************************************************	
* Purpose: Returns the value stored in the Array2D object at the specified
*			row and column position
*
* Entry: row is the row position in which the requested data is located
*		 column is the column position in which the requested data is located
*		 row and column must respectively be within the bounds 
*			of 0 <= row/column < m_row/m_column
*
* Exit: The data stored at the given row/column position is returned
*
************************************************************************/
template<typename T>
T& Array2D<T>::Select(int row, int column)
{
	return m_array[(row * m_col) + column];
}

#endif
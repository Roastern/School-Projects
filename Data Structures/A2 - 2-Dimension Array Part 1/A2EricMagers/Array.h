/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Assignment 1
* Filename:			Array.h
* Date Created:		3/31/2014
* Modifications:	4/2/2014 – Added documentation
************************************************************/

#ifndef ARRAY_H_
#define ARRAY_H_

/************************************************************************
* Class: Array
*
* Purpose: This class creates a dynamic one-dimensional array that can be 
*			started at any start index, or resized at any time
*
* Manager functions:	
* 	Array ( )
* 		The default size is zero and the start index is zero.  	
*	Array (int length, int start_index = 0)
*		Creates an appropriate sized array with the starting index 
*              either zero or the supplied starting value.
*	Array (const Array &copy)
*		Creates a new array which is a copy of the given copy array
*	operator = (const Array &rhs)
*		Copies over the rhs array into an already existing array object
*	~Array()
*		deletes the array
*
* Methods:		
*	operator [ ] (int index)
*		Returns the value stored in the array at the element indicated by 
*			the given index.
*	getLength ( ) 
*		Returns the length of the array.
*	getStartIndex ( )
*		Returns the starting index of the array.
*	setLength (int length)
*		Defines the array to having the number of elements equal to length
*	setStartIndex (int index)
*		Sets the starting index of the array to the given index.
*************************************************************************/
template<typename T>
class Array 
{
public:
	Array();
	Array(int length, int start_index = 0);
	Array(const Array<T>& copy);
	~Array();

	Array<T>& operator= (const Array &rhs);
	T& operator[] (int index) const;

	int getLength() const;
	int getStartIndex() const;
	void setLength(int length);
	void setStartIndex(int index);

private:
	T* m_array;
	int m_start_index;
	int m_length;
};

#endif
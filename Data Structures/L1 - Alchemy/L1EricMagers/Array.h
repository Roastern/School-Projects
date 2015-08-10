/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Assignment 1
* Filename:			Array.h
* Date Created:		3/31/2014
* Modifications:	4/2/2014 – Added documentation
*					4/8/2014 - Added function documentation
*					and moved function definitions to Array.h
************************************************************/

#ifndef ARRAY_H_
#define ARRAY_H_

#include "Exception.h"

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

/**********************************************************************	
* Purpose: Default constructor, initializes the array to be a nullptr
*			and initializes m_length and m_start_index to 0
*
* Entry: No values are entered
*
* Exit: No values are returned
*
************************************************************************/
template<typename T>
Array<T>::Array() : m_array(nullptr), m_length(0), m_start_index(0)
{

}

/**********************************************************************	
* Purpose: Overloaded constructor, initializes the Array object with the
*			input values
*
* Entry: length is the declared size of the array, start_index is the 
*			starting index for the array
*		 Both length and start_index must be non-negative
*
* Exit: No values are returned
*		an array of the data type <T> are created, the length of the array
*		is equal to length
*
************************************************************************/
template<typename T>
Array<T>::Array(int length, int start_index) : m_array(nullptr), m_start_index(0)
{
	setStartIndex(start_index);
	setLength(length);

	for (int i = 0; i < m_length; i++) 
		m_array[i] = T();
}

/**********************************************************************	
* Purpose: Copy constructor, initializes the array to to that of the 
*			copy object and initializes m_length and m_start_index
*			to be the same as the copy object
*
* Entry: copy is the Array object to be copied into the new Array object
*
* Exit: No values are returned
*		Creates a new array with the length and start index of the copy
*		object, and copies all members of copy's array into the new array
*
************************************************************************/
template<typename T>
Array<T>::Array(const Array<T>& copy) : m_start_index(copy.getStartIndex())
{
	setLength(copy.getLength());

	for (int i = 0; i < m_length; i++)
		m_array[i] = copy.m_array[i];
}

/**********************************************************************	
* Purpose: Default destructor, deletes the array and sets both m_length
*			and m_start_index to 0
*
* Entry: No values are entered
*
* Exit: No values are returned
*
************************************************************************/
template<typename T>
Array<T>::~Array() 
{
	delete [] m_array;
	m_array = nullptr;
	m_length = 0;
	m_start_index = 0;
}

/**********************************************************************	
* Purpose: Makes a copy of the given Array object and stores it in the
*			current array object
*
* Entry: rhs is the Array object to be copied
*
* Exit: The address of the current Array object is returned
*		A new array is created of the same length as the rhs object and
*			the data members are copied over
*		The old array of the current object is destroyed and the new 
*			array takes it's place
*
************************************************************************/
template<typename T>
Array<T>& Array<T>::operator=(const Array &rhs) 
{
	if (this->m_array != rhs.m_array)
	{
		delete [] this->m_array;
		this->m_array = nullptr;

		this->setLength(rhs.getLength());
		this->setStartIndex(rhs.getStartIndex());

		for (int i = 0; i < this->m_length; i++)
			this->m_array[i] = rhs.m_array[i];
	}

	return *this;
}

/**********************************************************************	
* Purpose: Finds an element within the array by evaluating the index
*
* Entry: index is the value entered and is used to determine a specific
*			position within the array
*		index must be less than the start index
*		index must be less than the start index + length of the array
*
* Exit: The value stored in the array at the given index is returned
*
************************************************************************/
template<typename T>
T& Array<T>::operator[](int index) const
{
	if (index > (m_start_index + m_length)) 
	{
		throw Exception("Index exceeds upper bounds");
	}
	else if (index < m_start_index) 
	{
		throw Exception("Index exceeds lower bounds");
	}
	index = index - m_start_index;
	return m_array[index];
}

/**********************************************************************	
* Purpose: Returns the length of the array
*
* Entry: No values are passed to this function
*
* Exit: m_length, the length of the array, is returned
*
************************************************************************/
template<typename T>
int Array<T>::getLength() const 
{
	return m_length;
}

/**********************************************************************	
* Purpose: Returns the starting index of the array
*
* Entry: No values are passed to this function
*
* Exit: m_start_index, the starting index of the array, is returned
*
************************************************************************/
template<typename T>
int Array<T>::getStartIndex() const 
{
	return m_start_index;
}

/**********************************************************************	
* Purpose: Creates a new array to be stored in the Array object and 
*			copies over data from the original array, if any
*
* Entry: length is the length of the new array
*		 length must be non-negative
*
* Exit: Nothing is returned
*		m_array is deleted, new array is set to m_array
*
************************************************************************/
template<typename T>
void Array<T>::setLength(int length) 
{
	if (length < 0) 
	{
		throw Exception("Length is not a valid number");
	}
	else 
	{
		T *new_array = new T[length];

		if (m_array == nullptr) 
		{
			m_array = new_array;
		}
		else 
		{				
			for (int i = 0; i < length; i++)
			{
				if (i < m_length)
					new_array[i] = m_array[i];
				else
					new_array[i] = T();
			}

			delete [] m_array;
			m_array = new_array;
		}

		m_length = length;
	}
}

/**********************************************************************	
* Purpose: Sets the starting index for the array
*
* Entry: start_index is the new starting index for the array
*
* Exit: Nothing is returned
*		m_start_index is set to the new starting index
*
************************************************************************/
template<typename T>
void Array<T>::setStartIndex(int start_index) 
{
	m_start_index = start_index;
}
#endif
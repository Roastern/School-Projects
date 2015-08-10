/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Assignment 1
* Filename:			Array.cpp
* Date Created:		3/31/2014
* Modifications:	4/2/2014 – Added documentation
************************************************************/
#ifndef ARRAY_CPP_
#define ARRAY_CPP_

#include "Array.h"
#include "Exception.h"

template<typename T>
Array<T>::Array() : m_array(nullptr), m_length(0), m_start_index(0)
{

}

template<typename T>
Array<T>::Array(int length, int start_index) : m_start_index(0)
{
	setStartIndex(start_index);
	setLength(length);

	for (int i = 0; i < m_length; i++) 
		m_array[i] = T();
}

template<typename T>
Array<T>::Array(const Array<T>& copy) : m_start_index(copy.getStartIndex())
{
	setLength(copy.getLength());

	for (int i = 0; i < m_length; i++)
		m_array[i] = copy.m_array[i];
}

template<typename T>
Array<T>::~Array() 
{
	if (m_array != nullptr) 
	{
		delete [] m_array;
		m_array = nullptr;
		m_length = 0;
	}
}

template<typename T>
Array<T>& Array<T>::operator=(const Array &rhs) 
{
	if (this->m_array == rhs.m_array)
		return *this;

	if (this->m_array != nullptr) 
	{
		delete [] this->m_array;
		this->m_array = nullptr;
	}
	this->setLength(rhs.getLength());
	this->setStartIndex(rhs.getStartIndex());

	for (int i = 0; i < this->m_length; i++)
		this->m_array[i] = rhs.m_array[i];

	return *this;
}

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

template<typename T>
int Array<T>::getLength() const 
{
	return m_length;
}

template<typename T>
int Array<T>::getStartIndex() const 
{
	return m_start_index;
}

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

template<typename T>
void Array<T>::setStartIndex(int start_index) 
{
	m_start_index = start_index;
}

#endif
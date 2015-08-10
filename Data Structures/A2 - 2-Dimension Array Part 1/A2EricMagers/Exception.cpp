/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Assignment 1
* Filename:			Exception.cpp
* Date Created:		4/1/2014
* Modifications:	4/2/2014 – Added documentation
************************************************************/


#define _CRT_SECURE_NO_WARNINGS

#include "Exception.h"
#include <string>

Exception::Exception() : m_msg(nullptr)
{
	
}

Exception::Exception(char *msg) : m_msg(nullptr)
{
		setMessage(msg);
}

Exception::Exception(const Exception &copy)
{
	if (copy.m_msg == nullptr)
		this->m_msg = nullptr;
	else 
	{
		setMessage(copy.getMessage());
	}
}

Exception::~Exception() 
{
	delete [] m_msg;
	m_msg = nullptr;
}

Exception& Exception::operator=(const Exception &rhs) 
{
	if (rhs.m_msg == nullptr)
		this->m_msg = nullptr;
	else 
	{
		this->setMessage(rhs.getMessage());
	}

	return *this;
}

const char* Exception::getMessage() const
{
	return m_msg;
}

void Exception::setMessage(const char *msg) {
	if (msg == nullptr)
		m_msg = nullptr;
	else 
	{
		if (m_msg != nullptr)
		{
			delete [] m_msg;
		}
		m_msg = new char[strlen(msg) +1];

		strcpy(m_msg, msg);
	}
}

ostream& operator<<(ostream& stream, const Exception &except)
{
	stream << except.getMessage() << endl;

	return stream;
}
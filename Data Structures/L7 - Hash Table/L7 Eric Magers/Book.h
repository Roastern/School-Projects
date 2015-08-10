/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 7
* Filename:			Book.h
* Date Created:		6/3/2014
* Modifications:	
*
************************************************************/

#ifndef BOOK_H_
#define BOOK_H_

#include <string>
using std::string;

struct Book
{
	string m_title;
	string m_author;
	int m_pages;
};

#endif
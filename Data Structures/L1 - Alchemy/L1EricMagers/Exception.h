/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Assignment 1
* Filename:			Exception.h
* Date Created:		4/1/2014
* Modifications:	4/2/2014 – Added documentation
************************************************************/

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <iostream>
using namespace std;


/************************************************************************
* Class: Exception
*
* Purpose: This class creates a an exception object which can be used to 
*			inform the client of errors. 
*
* Manager functions:	
* 	Exception ( )
* 		The default message is a nullptr.  	
*	Exception (char* msg)
*		Creates an exception with a message which is given by the argument
*              passed in the constructor.
*	Exception (const Exception &copy)
*		Creates an Exception object which is a copy of an existing 
*			Exception object
*	operator = (const Exception &rhs)
*		Copies the Exception object on the right hand side of the '='
*			operator to the one on the left hand side.
*	~Array()
*		Destroys the Exception message before destroying the object
*
* Methods:		
*	getMessage ( ) 
*		returns the message held in the Exception object
*	setMessage (const char *msg)
*		Copies msg into the Exceptions message
*	operator << (ostream &stream, const Exception &except)
*		Prints the Exception's message to the given ostream, then
*			returns the ostream address.
*************************************************************************/
class Exception {
public:
	Exception();
	Exception(char *msg);
	Exception(const Exception &copy);
	~Exception();

	Exception& operator=(const Exception &rhs);

	const char* getMessage() const;
	void setMessage(const char *msg);

	friend	ostream& operator<<(ostream &stream, const Exception &except);

private:
	char * m_msg;
};

#endif
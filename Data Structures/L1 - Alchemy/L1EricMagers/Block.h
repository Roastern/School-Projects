/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Assignment 2
* Filename:			Block.h
* Date Created:		4/6/2014
* Modifications:	4/8/2014 – Added documentation
************************************************************/

#ifndef BLOCK_H_
#define BLOCK_H_

#include <iostream>
#include <Windows.h>
#include "Exception.h"
using std::cout;

//default white on black color combo
const int DEFAULT_COLOR = 7;

/************************************************************************
* Class: GameBoard
*
* Purpose: This class creates a data type which stores a color (stored as
*			an int, and a symbol stored as a char
*
* Manager functions:	
* 	Block ( )
* 		Initializes the Block object to default values, ' ' for the symbol
*			and 7, default white on black, for the color
*	Block (int foreground, int symbol)
*		Initializes the Block object to the appropriate values
*	Block (const Block &copy)
*		Initializes the Block to have the same values as the copy object
*	~BLock ( )
*		Deletes the Block object
*	operator = (const Block &rhs)
*		Copies rhs into the specified Block object
*
* Methods:
*	getFColor ( )
*		Returns m_f_ground, the color stored in the Block object
*	setFColor (int foreground)
*		Sets the m_f_ground to foreground
*	getSymbol ( )
*		Returns m_symbol, the symbol stored in the Block object
*	setSymbol (char symbol)
*		Sets m_symbol to symbol
*	operator<< (ostream &stream, const Block &block)
*		Prints block to the stream ostream
*************************************************************************/
class Block
{
	public:
	Block();
	Block(int foreground, char symbol);
	Block(const Block &copy);
	~Block();

	Block& operator= (const Block &rhs);

	int getFColor() const;
	void setFColor(int foreground);
	char getSymbol() const;
	void setSymbol(char symbol);	

	friend	ostream& operator<<(ostream &stream, const Block &block);

private:
	int m_f_ground;
	char m_symbol;

};

#endif
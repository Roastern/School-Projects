#ifndef BLOCK_CPP_
#define BLOCK_CPP_

#include "Block.h"

HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

/**********************************************************************	
* Purpose: Initializes m_f_ground and m_symbol to default values
*
* Entry: No values are passed to this function
*
* Exit: Nothing is returned
*		m_f_ground is initialized to the default color int, 7, m_symbol 
*		is initialized to the default character ' '
*
************************************************************************/
Block::Block() : m_f_ground(DEFAULT_COLOR), m_symbol(' ')
{

}

/**********************************************************************	
* Purpose: Initializes m_f_ground and m_symbol to given values
*
* Entry: foreground is the int color value to be stored in m_f_ground
*		 symbol is the character to be stored in m_symbol
*
* Exit: No values are returned
*		m_f_ground is initialized to foreground and m_symbol is 
*		initialized to symbol
*
************************************************************************/
Block::Block(int foreground, char symbol) : m_f_ground(foreground), m_symbol(symbol)
{

}

/**********************************************************************	
* Purpose: Initializes m_f_ground and m_symbol to the values stored in
*			copy
*
* Entry: copy is the Block object to be copied into the new Block object
*
* Exit: No values are returned
		m_f_ground initialized to be that of cop's m_f_ground, and 
*		symbol is initialized to be that of copy's symbol
*
************************************************************************/
Block::Block(const Block &copy) :  m_f_ground(copy.getFColor()), m_symbol(copy.getSymbol())
{

}

/**********************************************************************	
* Purpose: Destroys the block object
*
* Entry: No values are passed to this function
*
* Exit: No values are returned by this function
*
************************************************************************/
Block::~Block()
{

}

/**********************************************************************	
* Purpose: Sets the values of the current Block object to those stored 
*			in the given Block object
*
* Entry: rhs is the Block object to be copied
*
* Exit: The address of the current Block object is returned
*		m_f_ground is set to rhs's m_f_ground
*		m_symbol is set to rhs's m_symbol
*
************************************************************************/
Block& Block::operator= (const Block& rhs)
{
	this->setFColor(rhs.getFColor());
	this->setSymbol(rhs.getSymbol());

	return *this;
}

/**********************************************************************	
* Purpose: Returns the value stored in m_f_ground
*
* Entry: No values are passed to this function
*
* Exit: m_f_ground is returned
*
************************************************************************/
int Block::getFColor() const
{
	return m_f_ground;
}

/**********************************************************************	
* Purpose: Sets m_f_ground to the given value
*
* Entry: foreground is the value to be stored in m_f_ground
*
* Exit: No value is returned
*		m_f_ground is set to foreground
*
************************************************************************/
void Block::setFColor(int foreground)
{
	if ((foreground < 0) || (foreground > 255))
		throw Exception("Invalid color");

	m_f_ground = foreground;
}

/**********************************************************************	
* Purpose: Returns the value stored in m_symbol
*
* Entry: No values are passed to this function
*
* Exit: m_symbol is returned
*
************************************************************************/
char Block::getSymbol() const
{
	return m_symbol;
}

/**********************************************************************	
* Purpose: Sets m_symbol to the given value
*
* Entry: foreground is the value to be stored in m_symbol
*
* Exit: No value is returned
*		m_symbol is set to foreground
*
************************************************************************/
void Block::setSymbol(char symbol)
{
	m_symbol = symbol;
}

/**********************************************************************	
* Purpose: Prints the given Block object to the given output stream
*
* Entry: stream is the output stream which will be written to
*		 block is the Block object to be written
*
* Exit: The address of the given output stream is returned
*		m_symbol is written with the text/background color modification
*		stored in m_f_ground
*
************************************************************************/
ostream& operator<< (ostream &stream, const Block &block)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(handle, &csbi);

	SetConsoleTextAttribute(handle, block.getFColor());
	
	stream << block.getSymbol();

	SetConsoleTextAttribute(handle, csbi.wAttributes);

	return stream;
}

#endif
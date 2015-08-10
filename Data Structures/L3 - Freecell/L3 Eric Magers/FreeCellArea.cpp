/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 3
* Filename:			FreeCellArea.cpp
* Date Created:		4/29s/2014
* Modifications:	
*
************************************************************/

#ifndef FREECELLAREA_CPP_
#define FREECELLAREA_CPP_

#include "FreeCellArea.h"

/**********************************************************************	
* Purpose: Initializes the FreeCellArea to have an Array of size 
*		   NUMOFFREECELLS
*
* Entry: No values are passed to this function
*
* Exit: Nothing is returned
*
************************************************************************/
FreeCellArea::FreeCellArea() : f_cells(NUMOFFREECELLS)
{

}

/**********************************************************************	
* Purpose: Initializes the FreeCellArea to have a copy of the Array 
*		   stored in copy
*
* Entry: copy is the FreeCellArea to be copied
*
* Exit: copy's Array of free cells is copied
*
************************************************************************/
FreeCellArea::FreeCellArea(const FreeCellArea & copy) : f_cells(copy.f_cells)
{

}

/**********************************************************************	
* Purpose: Copies the array of cards from copy into the current object
*
* Entry: copy is the FreeCellArea to be copied
*
* Exit: The current FreeCellArea is returned
*
************************************************************************/
FreeCellArea & FreeCellArea::operator= (const FreeCellArea & copy)
{
	if (this != &copy)
	{
		f_cells = copy.f_cells;
	}

	return *this;
}

/**********************************************************************	
* Purpose: Destroys the FreeCellArea object
*
* Entry: No values are passed to this function
*
* Exit: Nothing is returned
*
************************************************************************/
FreeCellArea::~FreeCellArea()
{

}

/**********************************************************************	
* Purpose: Prints the Array of free cells
*
* Entry: No values are passed to this function
*
* Exit: Nothing is returned
*
************************************************************************/
void FreeCellArea::PrintFreeArea() const 
{
	for (int i = 0; i < NUMOFFREECELLS; i++)
	{
		if (!(f_cells[i] == Card()))
		{
			if (f_cells[i].getCard_F() == 10)
				cout << f_cells[i] << " ";
			else
				cout << f_cells[i] << "  ";
		}
		else 
			cout << "    ";
	}
}

/**********************************************************************	
* Purpose: Places the given card into the given position of the Array
*
* Entry: nCard is the card to be placed into the array, cell is the 
*		 position in the array the card is to be placed
*
* Exit: nCard is placed in the array
*		Nothing is returned
*
************************************************************************/
void FreeCellArea::PlaceCard(const Card nCard, int cell)
{
	if (!(isMoveValid(cell)))
		throw Exception("Cannot place the card on a full free cell");

	f_cells[cell] = nCard;
}

/**********************************************************************	
* Purpose: Returns a constant pointer to the card at the given position
*
* Entry: cell is the position within the array
*
* Exit: A reference to the given card is returned
*
************************************************************************/
const Card * FreeCellArea::ReferenceCard(int cell)
{
	const Card * temp = nullptr;

	if (f_cells[cell].getCard_F() != 0)
		temp = &f_cells[cell];

	return temp;
}

/**********************************************************************	
* Purpose: Removes a card from the given position within the array
*
* Entry: cell is the given position within the array with the card to 
*		 be returned
*
* Exit: The removed card is returned
*
************************************************************************/
Card FreeCellArea::RemoveCard(int cell)
{
	if (f_cells[cell].getCard_F() == 0)
		throw Exception("This free cell is empty");

	Card temp = f_cells[cell];
	f_cells[cell] = Card();

	return temp;
}

/**********************************************************************	
* Purpose: Returns the number of empty cells stored in the array
*
* Entry: No values are passed to this function
*
* Exit: The number of empty cells in the array
*
************************************************************************/
int FreeCellArea::getNumOfEmptyCells() const
{
	int n_empty_cells = 0;

	for (int i = 0; i < NUMOFFREECELLS; i++)
	{
		if (f_cells[i].getCard_F() == 0)
			n_empty_cells++;
	}

	return n_empty_cells;
}

/**********************************************************************	
* Purpose: Checks to see if the given cell is empty and can have a card
*		   placed in it
*
* Entry: cell is the position in the array to be checked
*
* Exit: True is returned if a card can be placed in the cell
*		False is returned if the card can not
*
************************************************************************/
bool FreeCellArea::isMoveValid(int cell)
{
	bool valid = true;

	if (f_cells[cell].getCard_F() != 0)
		valid = false;

	return valid;	
}

#endif
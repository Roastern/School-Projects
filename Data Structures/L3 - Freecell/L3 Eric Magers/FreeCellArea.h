/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 3
* Filename:			FreeCellArea.h
* Date Created:		4/29/2014
* Modifications:	
*
************************************************************/

#ifndef FREECELLAREA_H_
#define FREECELLAREA_H_

#include "Array.h"
#include "Card.h"

//constant number of free cells
const int NUMOFFREECELLS = 4;

/************************************************************************
* Class: FreeCellArea
*
* Purpose: Stores an array of cards to be used as free cells
*
* Manager functions:	
* 	FreeCellArea ( )
* 		Creates an Array of Cards to represent free cels
*	FreeCellArea (const FreeCellArea & copy)
*		Creates a copy of the copy FreeCellArea
*	operator = (const FreeCellArea & copy)
*		Copies the Array of cards from copy into the current FreeCellArea
*	~FreeCellArea ( )
*		deletes the Array of cards
*
* Methods:		
*	PrintFreeArea ( )
*		Prints the cards in the free cells
*	PlaceCard (const Card nCard, int cell)
*		Places the given card in the given free cell
*	ReferenceCard (int cell)
*		Returns a pointer to the card in the given free cell
*	RemoveCard (int cell)
*		Removes the card in the given free cell
*	getNumOfEmptyCells ( ) const
*		Returns the number of free cells that are empty
*		
*************************************************************************/
class FreeCellArea
{
public:
	FreeCellArea();
	FreeCellArea(const FreeCellArea & copy);
	FreeCellArea & operator= (const FreeCellArea & copy);
	~FreeCellArea();

	void PrintFreeArea() const;

	void PlaceCard(const Card nCard, int cell);
	const Card * ReferenceCard(int cell);
	Card RemoveCard(int cell);
	int getNumOfEmptyCells() const;

private:
	bool isMoveValid(int cell);
	Array<Card> f_cells;
};

#endif
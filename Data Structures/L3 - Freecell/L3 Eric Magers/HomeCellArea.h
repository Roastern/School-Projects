/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 3
* Filename:			HomeCellArea.h
* Date Created:		4/29/2014
* Modifications:	
*
************************************************************/

#ifndef HOMECELLAREA_H_
#define HOMECELLAREA_H_

#include "AStack.h"
#include "Array.h"
#include "Card.h"

//constant value of the number of columns for the home area
const int NUMOFHOMECOLUMNS = 4;

/************************************************************************
* Class: HomeCellArea
*
* Purpose: Creates an array of stacks to store cards
*
* Manager functions:	
* 	HomeCellArea ( )
* 		Initiates the Array of stacks to be of size NUMOFHOMECOLUMNS
*	HomeCellArea (const HomeCellArea & copy)
*		Creates a copy of the copy HomeCellArea
*	operator = (const HomeCellArea & copy)
*		Copies the Array of stacks from copy into the current HomeCellArea
*	~HomeCellArea ( )
*		deletes the Array of stacks
*
* Methods:		
*	PrintHomeArea ( )
*		Prints the cards stored in the array of stacks
*	MoveCard (const Card & nCard)
*		Places the given card in a home column
*	isWin ( ) const
*		Checks to see if all the columns of the home area are full
*	CheckAutoAdd (const Card * nCard)
*		checks to see if the given card should be automatically added to
*		the home cell
*	isMoveValid (const Card & nCard)
*		checks to see if the given card can be placed in the home area
*		
*************************************************************************/
class HomeCellArea
{
public:
	HomeCellArea();
	HomeCellArea(const HomeCellArea & copy);
	HomeCellArea & operator= (const HomeCellArea & copy);
	~HomeCellArea();

	void PrintHomeArea() const;

	void MoveCard(const Card & nCard);
	bool isWin() const;
	bool CheckAutoAdd(const Card * nCard);

private:
	int isMoveValid(const Card & nCard);
	Array<AStack<Card>> h_cells;

};


#endif
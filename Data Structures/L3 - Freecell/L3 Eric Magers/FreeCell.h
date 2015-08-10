/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 3
* Filename:			FreeCell.h
* Date Created:		4/29/2014
* Modifications:	
*
************************************************************/

#ifndef FREECELL_H_
#define FREECELL_H_

#include <iostream>
#include "GameBoard.h"
using std::cout;
using std::cin;

/************************************************************************
* Class: FreeCell
*
* Purpose: Runs the game FreeCell
*
* Manager functions:	
* 	FreeCell ( )
* 		Calls PlayGame to initiate a GameBoard and to run FreeCell
*	~FreeCell ( )
*		Destroys the FreeCell object
*
* Methods:		
*	GetSeed ( )
*		Retrieves the desired seed from the player
*	PlayGame ( ) 
*		Runs FreeCell
**************************************************************************/
class FreeCell
{
public:
	FreeCell();
	~FreeCell();

	int GetSeed();
	void PlayGame();
};

#endif
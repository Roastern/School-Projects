/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 3
* Filename:			GameBoard.h
* Date Created:		4/29/2014
* Modifications:	
*
************************************************************/

#ifndef GAMEBOARD_H_
#define GAMEBOARD_H_

#include "PlayArea.h"
#include "HomeCellArea.h"
#include "FreeCellArea.h"

const int MAXMOVECHARS = 10;


/************************************************************************
* Class: GameBoard
*
* Purpose: Stores a PlayArea, FreeCellArea, HomeCellArea and moves cards
*		   in between the three
*
* Manager functions:	
* 	GameBoard ( )
* 		Initiates all areas to default settings
*	GameBoard (int seed)
*		Initiates FreeCellArea and HomeCellArea and PlayArea with seed
*	GameBoard (const GameBoard & copy)
*		Copies the PlayArea, FreeCellArea, and HomeCellAreas from copy into
*		the new GameBoard
*	operator = (const GameBoard & copy)
*		Copies the PlayArea, FreeCellArea, and HomeCellAreas from copy into
*		the current GameBoard
*	~GameBoard ( )
*		deletes the FreeCellArea, PlayArea, and HomeCellArea
*
* Methods:		
*	PrintBoard ( )
*		Prints the FreeCellArea, PlayArea and HomeCellArea
*	GetMove ( )
*		Retrieves the move from the player
*	EndGame ( )
*		Determines whether or not the game has ended
*	isMoveValid ( )
*		Determines whether or not the given move specifies a move from
*		the play area or freecellarea, calls checkPMove or checkFMove
*		respectively
*	tokenize ( )
*		tokenizes the given move
*	checkPMove ( )
*		validates the given move and moves the card(s)
*	checkFMove ( )
*		validates the given move and moves the card
*	printInstructions ( )
*		prints the format in which the moves are to be made
*	checkCTHome ( )
*		checks the top cards of each PlayArea stack as well as the cards
*		cards in the FreeCellArea to see if they can be automatically added
*		to home, moves them if they can
**************************************************************************/
class GameBoard
{
public:
	GameBoard();
	GameBoard(int seed);
	GameBoard(const GameBoard & copy);
	GameBoard & operator= (const GameBoard & copy);
	~GameBoard();

	void PrintBoard() const;
	void GetMove();
	bool EndGame() const;

private:
	bool isMoveValid();
	bool tokenize();
	bool checkPMove();
	bool checkFMove();
	void printInstructions();
	void checkCTHome();

	PlayArea p_area;
	HomeCellArea h_area;
	FreeCellArea f_area;

	char * move;
	char * tok;
};

#endif
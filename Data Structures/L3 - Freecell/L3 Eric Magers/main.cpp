/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 3
* Filename:			main.cpp
* Date Created:		4/27/2014
* Modifications:	
*
* Overview:
*	This program runs FreeCell
*
* Input:
*	The input will start as a numerical or alpha numeric for
*	the game seed or exit. During the game, both letters and
*	numbers are used to specify which cards are to be moved where.
*	Card moves will be in the following format:
*
*	[area: p or f][PlayArea row: a-z][column: 1-8][dest area: p, f, or h][play\free column]
*
*	If moving from the PlayArea, row is required, if moving to the home area, no
*	destination column is required.
*
*	An example of valid moves would be:
*	F 0 P 2 -   Moving from the first free cell to the third play area column
*	P G 1 H -   Moving the card in the G row of the 2nd column in the play area
*			    to the home area
*	P G 1 F 1 - Moving the card from the G row of the 2nd column in the play area
*				to the 2nd free cell
*	P E 1 P 3 - Moving the stack of cards up to and including row E from the 2nd
*				column of the PlayArea to the 4th column of the PlayArea
*
*	You can also type 'help' while playing the game to see the move requirements
*
*	Note that the program accepts both lower case or upper
*	case characters.
*
* Output:
*	The output of this program will be one of the following:
*	Game's start:
*		Prompts the user to enter the desired seed, or to quit
*	Instructions:
*		If the user types 'help' during the game, the move requirements are
*		printed above the game board
*	Game play:
		The game board is printed in three areas, the upper left area are the 
*		free cells, upper right area are the home cells, and the bottom area 
*		is the play area.
*
*		An example of the game play output is as follows:
*
*	Free Area			Home Area
*	0 1 2 3				  0 1 2 3
*
*		   Play Area
*       0 1 2 3 4 5 6 7
*    a 
*	 b
*	 c
*	 d
*	 e	
*	 f	
*	 g 
*
*	 Please enter your move or type 'help' for move options
*
*	Once the game has been won, an appropriate message will be output
*
************************************************************/

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "FreeCell.h"
#include <iostream>
using std::cout;
using std::end;
using std::cin;

int main()
{
	bool hi = false;
	FreeCell newGame;

	_CrtDumpMemoryLeaks();
	return 0;
}
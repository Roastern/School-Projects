/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 3
* Filename:			FreeCell.cpp
* Date Created:		4/29/2014
* Modifications:	
*
************************************************************/

#ifndef FREECELL_CPP_
#define FREECELL_CPP_

#include "FreeCell.h"

/**********************************************************************	
* Purpose: Calls PlayGame to start a game of FreeCell
*
* Entry: Nothing is passed into this function
*
* Exit: Nothing is returned
*
************************************************************************/
FreeCell::FreeCell()
{
	PlayGame();
}

/**********************************************************************	
* Purpose: Destroys the FreeCell object
*
* Entry: Nothing is passed into this function
*
* Exit: Nothing is returned
*
************************************************************************/
FreeCell::~FreeCell()
{

}

/**********************************************************************	
* Purpose: Gets the desired game seed from the user and returns it to
*		   PlayGame
*
* Entry: Nothing is passed into this function
*
* Exit: The desired seed is returned
*
************************************************************************/
int FreeCell::GetSeed()
{
	char * seedy = new char[8];
	int seed;

	cout << "Please enter the game number (between 0 and 1000000) you wish to play" << endl
			<< " 0 for a random game, quit to exit: ";
	cin.getline(seedy, 8);

	if (cin.fail())
	{
		cin.clear();
		cin.ignore(8, '\n');
	}

	seed = atoi(seedy);

	if (strcmp(seedy, "quit") == 0 || strcmp(seedy, "Quit") == 0)
		seed = -1;

	delete seedy;

	return seed;
}

/**********************************************************************	
* Purpose: Runs the FreeCell game
*
* Entry: Nothing is passed into this function
*
* Exit: Nothing is returned
*
************************************************************************/
void FreeCell::PlayGame()
{
	bool playgame = true;
	bool won = false;

	GameBoard newGame;

	while (playgame)
	{
		int seed = GetSeed();

		if (seed > 0)
			newGame = GameBoard(seed);
		else if (seed < 0)
			playgame = false;

		system("cls");

		while (!won && playgame)
		{
			newGame.PrintBoard();
			newGame.GetMove();
			won = newGame.EndGame();
			cout << endl << endl << endl;
		}

		if (won == true)
			cout << endl << "Congratulations! You beat FreeCell!" << endl << endl << endl;

		newGame = GameBoard();
		won = false;
	}
}

#endif
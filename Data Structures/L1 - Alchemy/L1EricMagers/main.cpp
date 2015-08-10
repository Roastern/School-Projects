/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 1
* Filename:			main.cpp
* Date Created:		4/6/2014
* Modifications:	4/8/2014 – Removed game logic from main 
*							   and placed in Alchemy.h
*
* Overview:
*	This program will present a menu for the user to choose from.
*	The user will be able to print instructions on how to play
*	alchemy, or play the game.
*
* Input:
*	The input will consist of the numerical option in the 
*	games main menu, and then the letter-numerical option
*	for where the user would like to place the block on the
*	Alchemy board. The placement input will be in the form 
*	of:
*
*	[a-h][0-9]
*	a1, C4
*	or to discard a Block, the user may enter:
*	dd
*
*	Note that the program accepts both lower case or upper
*	case characters.
*
* Output:
*	The output of this program will be one of the following:
*	Main Menu:
*		Prints a menu with choices which dictate how the program
*		continues to run
*	Instructions:
*		Intructions will print a blank board and then provide
*		a brief description on how to know where to place the
*		block and how to input your position choice.
*	Game play:
		Throughout the game, the board is printed along with the 
*		score, number of discards, the block to be added to the
*		board, and a message prompting the user to enter their selection.
*		Additionally, any errors are printed if the move the user selected 
*		is invalid.
*
*		An example of the game play output is as follows:
*       1 2 3 4 5 6 7 8 9
*      ###################
*    a # # # # # # # # # #
*      ###################
*	 b # # # # # # # # # #
*      ###################
*	 c # # # # # # # # # #
*      ###################
*	 d # # # # # # # # # #
*      ###################
*	 e # # # # # # # # # #		SCORE: 0
*      ###################
*	 f # # # # # # # # # #		DISCARDS: 0
*      ###################
*	 g # # # # # # # # # #
*      ###################
*	 h # # # # # # # # # #
*      ###################
*	 Select the position to place *
*	 Must be in the format of (a-h)(1-9), such as c7 (dd to discard): 
*
*		Once the game has been won or lost, an appropriate message will displace
*		along with the accumulated score.
************************************************************/


#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include "Alchemy.h"
using namespace std;

void menu();
void playGame();
void instructions();

int main()
{
	Alchemy alchemy;
	alchemy.mainMenu();

	#ifdef _WIN32
	if (_CrtDumpMemoryLeaks()) {
		cout << "Memory leaks!" << endl;
	}
	#endif

	char c;
	cin >> c;
	return 0;
}

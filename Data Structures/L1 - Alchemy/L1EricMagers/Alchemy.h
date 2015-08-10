/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Assignment 2
* Filename:			Alchemy.h
* Date Created:		4/8/2014
* Modifications:	
************************************************************/

#ifndef ALCHEMY_H_
#define ALCHEMY_H_

/************************************************************************
* Class: Alchemy
*
* Purpose: This class is the controller for the game Alchemy, it provides
*			the game logic as well as a menu for the game
*
* Methods	
* 	Alchemy ( )
* 		Creates the Alchemy object, no member variables need to be initialized
*	~Alchemy ( )
*		Destroys the Alchemy object
*	mainMenu ( )
*		Prints a game menu
*	printInstructions ( )
*		Prints instructions on how to play Alchemy
*	playAlchemy ( )
*		Runs the game
*	printAd ( )
*		Prints an ad before the game starts
*	sleep (int time)
*		Stalls the continuation of the program for the given amount of time
/************************************************************************/

#include <iostream>
#include <time.h>
#include "GameBoard.h"
using std::cout;
using std::cin;

class Alchemy
{
public:
	Alchemy();
	Alchemy(ostream &out_stream);
	~Alchemy();
	void mainMenu();
	void printInstructions() const;
	void playAlchemy();
	void printAd();
	void sleep(int time);

private:
	ostream& stream;
};

#endif
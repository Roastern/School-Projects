/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Assignment 2
* Filename:			Alchemy.cpp
* Date Created:		4/8/2014
* Modifications:	4/9/2014 - Finished adding instructions
							 - Added the printAd and sleep functions
************************************************************/

#include "Alchemy.h"

/**********************************************************************	
* Purpose: Default constructor, stream is initialized to cout by default
*
* Entry: No values are passed into this function
*
* Exit: No values are returned by this function	
*
************************************************************************/
Alchemy::Alchemy() : stream(cout)
{

}

/**********************************************************************	
* Purpose: The output stream for Alchemy is initialized to the user
*			specified stream
*
* Entry: out_stream is the ostream that the user wishes Alchemy's output
*			to be printed to
*
* Exit: No values are returned by this function	
*
************************************************************************/
Alchemy::Alchemy(ostream &out_stream) : stream(out_stream)
{

}

/**********************************************************************	
* Purpose: Default destructor, Alchemy object is destroyed
*
* Entry: No values are passed into this function
*
* Exit: No values are returned by this function	
*
************************************************************************/
Alchemy::~Alchemy()
{

}

/**********************************************************************	
* Purpose: Prints menu options for the user to choose from
*
* Entry: option is the value that stores the users menu choice
*
* Exit: One of the following functions is called based on the users input	
*		 playAlchemy()
*		 printInstructions()
*
************************************************************************/
void Alchemy::mainMenu()
{
	char option;
	bool run = true;
	while(run)
	{
		system("cls");
		cout << "Welcome to Alchemy!" << endl
			<< "Please select one of the following options: " << endl
			<< "1. Play a new game" << endl
			<< "2. View instructions" << endl
			<< "3. Exit" << endl << endl;
		cout << "Enter your option: ";

		cin.get(option);
		cin.clear();
		cin.ignore(1, '\n');

		if (option == '1')
		{
			printAd();
			playAlchemy();
		}
		else if (option == '2')
		{
			printInstructions();
		}
		else if (option == '3')
		{
			run = false;
		}
		else
			cout << endl << endl << "Please enter a valid option" << endl;
	}
}

/**********************************************************************	
* Purpose: Runs the Alchemy game
*
* Entry: Creates a GameBoard object and loops, calling GameBoard's getMove()
*		  until a game-over criteria is met
*
* Exit: No values are returned by this function	
*
************************************************************************/
void Alchemy::playAlchemy()
{
	GameBoard m_gameboard(stream);
	bool gameRunning = true;

	while (gameRunning)
	{
		m_gameboard.getMove();

		if (m_gameboard.getDiscard() > 3)
		{
			stream << endl << "Game Over!" << endl
				<< "Your ending score: " << m_gameboard.getScore();
			m_gameboard.clearBoard();
			gameRunning = false;

			stream << endl << endl;
			system("pause");
		}
		else if (m_gameboard.getEmptyBlocks() == 0)
		{
			if (m_gameboard.getLevel() < 2)
			{
				stream << "You beat the level!" << endl
					<< "Your current score: " << m_gameboard.getScore() << endl
					<< "starting next level." << endl;
				m_gameboard.incLevel();
				m_gameboard.clearBoard();
			}
			else
			{
				stream << "Congratulations, you beat Alchemy!" << endl
					<< "Your final score: " << m_gameboard.getScore() << endl;
				gameRunning = false;
			}
		}
	}	
}

/**********************************************************************	
* Purpose: Prints the instructions for how to place Alchemy
*
* Entry: No values are passed into this function
*
* Exit: No values are returned by this function	
*
************************************************************************/
void Alchemy::printInstructions() const
{
	GameBoard instr(stream);
	Block freeBlock(GRAY, '#');
	Block bombBlock(DEFAULT, '@');
	Block example(BLUE, '*');

	system("cls");

	stream << "***How to play Alchemy***" << endl << endl
			<< "In Alchemy, you are provided with the following game board:" << endl << endl;
			instr.printBoard();

	stream << endl << "The objective is to get all the empty blocks within the board to have" << endl << " a gold background." << endl << endl
			<< "To do this, you will have to place randomly generated symbols within the board." << endl
			<< "To place a symbol, you will use the row and column identifiers to find the " << endl << " position on the board you would like it to be placed, "
			<< "and then type that" << endl << " combination when prompted." << endl
			<< "For instance, if I wanted to place " << example << " next to the free block in the center," << endl << " I would type: e3" << endl
			<< "If you cannot place the given block, or do not wish to play it, you can discard  it by entering 'dd'." << endl << endl
			<< "**WARNING** Having more than 3 discards held against you will cause you to lose." << endl
			<< "You can see how many discards are currently being held against you to the" << endl << " right of the game board." << endl << endl;

	stream	<< "Each symbol has a color, and with two exceptions, these symbols can only be" << endl << " placed in blocks whose surrounding blocks are of the same symbol or color." << endl
			<< "The two exceptions to this rule are: " << endl
			<< "\t" << freeBlock << ": which can be placed next to any symbols or colors on the board," << endl << "\t though at least one of the surrounding blocks must be filled" << endl << endl
			<< "\t" << bombBlock << ": which must be placed on a block which already has a symbol on it," << endl << "\t this will destroy the previously placed symbol and the block will" << endl << "\t become empty" << endl << endl;

	stream << "When all the blocks within a row and/or column have symbols placed in them, the  symbols are cleared. However, any time a symbol is cleared" << endl << " the gold color in the block remain." << endl
			<< "Once you have changed the color of every block on the game board, the board is" << endl << " reset and you progress to the next level where there will be" << endl << " more colors and more types of symbols." << endl << endl;

	system("pause");
}

/**********************************************************************	
* Purpose: Prints an Ad before the game begins, like every other Alchemy
*			game on the internet (this was supposed to be as accurate as
*			possible, right???)
*
* Entry: called by mainMenu()
*
* Exit: No values are returned by this function	
*
************************************************************************/
void Alchemy::printAd()
{
	for (int i = 15; i >=0; i--)
	{
		stream << "***PLEASE ENJOY THIS AD FROM OUR SPONSORS BEFORE YOUR GAME STARTS***" << endl
				<< "******************************" << i << "************************************" << endl
				<< "*                                                                  *" << endl
				<< "*                  VISIT BOB'S FRIED CHICKEN                      *" << endl
				<< "*                THE BEST FRIED CHICKEN IN TOWN                    *" << endl
				<< "*         EVEN YOUR MAMA'S COOKING WILL BE PUT TO SHAME            *" << endl
				<< "*                   OPEN ALL DAY, EVERY DAY                        *" << endl
				<< "*                                                                  *" << endl
				<< "********************************************************************" << endl << endl;

		sleep(1000);
		system("cls");
	}
}

/**********************************************************************	
* Purpose: Stalls the continuation of the program for the given amount
*			of miliseconds before returning control back to the calling
*			function
*
* Entry: time is the amount of time in miliseconds to be stalled
*
* Exit: No values are returned by this function	
*
************************************************************************/
void Alchemy::sleep(int time)
{
	clock_t time_to_meet = time + clock();
	while(time_to_meet > clock())
	{
		//nothing is done during the loop
		//clock()'s time keeps increasing until it is greater than time_to_meet
	}
}
/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 3
* Filename:			GameBoard.cpp
* Date Created:		4/29/2014
* Modifications:	
*
************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#ifndef GAMEBOARD_CPP_
#define GAMEBOARD_CPP_

#include <iostream>
#include <stdio.h>
#include "GameBoard.h"
using std::cout;
using std::gets;

/**********************************************************************	
* Purpose: Initializes p_area, h_area and f_area to default values
*
* Entry: Nothing is passed to this function
*
* Exit: Nothing is returned
*
************************************************************************/
GameBoard::GameBoard() : p_area(), h_area(), f_area(), move(nullptr)
{

}

/**********************************************************************	
* Purpose: Initializes h_area and f_area to default values, p_area is 
*		   initialized with the given seed
*
* Entry: seed is the int value to be passed into p_area
*
* Exit: Nothing is returned
*
************************************************************************/
GameBoard::GameBoard(int seed) : p_area(seed), h_area(), f_area(), move(nullptr)
{

}

/**********************************************************************	
* Purpose: Initializes p_area, h_area and f_area with the respective 
*		   areas stored in copy
*
* Entry: copy is the game board to be copied
*
* Exit: Nothing is returned
*
************************************************************************/
GameBoard::GameBoard(const GameBoard & copy) : p_area(copy.p_area), h_area(copy.h_area),
											   f_area(copy.f_area), move(nullptr)
{

}

/**********************************************************************	
* Purpose: p_area, h_area and f_area are copied 		   
*
* Entry: copy is the GameBoard to be copied
*
* Exit: Nothing is returned
*
************************************************************************/
GameBoard & GameBoard::operator= (const GameBoard & copy)
{
	if (this != &copy)
	{
		p_area = copy.p_area;
		h_area = copy.h_area;
		f_area = copy.f_area;
	}

	return *this;
}

/**********************************************************************	
* Purpose: destroys p_area, h_area and f_area are copied 		   
*
* Entry: Nothing is passed to this function
*
* Exit: Nothing is returned
*
************************************************************************/
GameBoard::~GameBoard()
{

}

/**********************************************************************	
* Purpose: Prints p_area, h_area and f_area		   
*
* Entry: Nothing is passed to this function
*
* Exit: Nothing is returned
*
************************************************************************/
void GameBoard::PrintBoard() const
{
	cout << "(F)ree Cells \t\t\t (H)ome Cells" << endl;

	for (int i = 0; i < 4; i++)
	{
		cout << i << "   ";
	}

	cout << "\t\t";

	for (int i = 0; i < 4; i++)
	{
		cout << i << "   ";
	}

	cout << endl;

	f_area.PrintFreeArea();
	cout << "\t\t";
	h_area.PrintHomeArea();

	cout << endl << endl << endl << "\t   (P)lay Area" << endl;

	p_area.PrintPlayArea();
}

/**********************************************************************	
* Purpose: Retrieves the move from the client
*
* Entry: Nothing is passed into this function
*
* Exit: Nothing is returned
*
************************************************************************/
void GameBoard::GetMove()
{
	bool move_got = false;

	cout << "Please enter your move or type 'help' for move options: ";

	move = new char[MAXMOVECHARS];

	cin.getline(move, MAXMOVECHARS);
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(100, '\n');
	}

	if (strcmp(move, "help") == 0 || strcmp(move, "Help") == 0)
	{
		printInstructions();
	}
	else
	{
		tok = strtok(move, " ");

		system("cls");

		move_got = isMoveValid();

		if (!move_got)
			cout << "Please enter a valid move";

		tok = nullptr;
	}

	checkCTHome();

	delete [] move;
}

/**********************************************************************	
* Purpose: Checks to see if winning conditions have been met
*
* Entry: Nothing is passed into this function
*
* Exit: True is returned if the game has ended
*		False is returned if not
*
************************************************************************/
bool GameBoard::EndGame() const
{
	return h_area.isWin();
}

/**********************************************************************	
* Purpose: Checks to see whether or not the first position of move is
*		   valid, then calls checkPMove or checkFMove to complete the 
*		   clients move
*
* Entry: Nothing is passed into this function
*
* Exit: Returns true if the move is valid, false if not
*
************************************************************************/
bool GameBoard::isMoveValid()
{
	bool valid = true;

	if (tok == nullptr)
		valid = false;

	if (valid)
	{
		if (*tok == 'P' || *tok == 'p')
			valid = checkPMove();
		else if (*tok == 'F' || *tok == 'f')
			valid = checkFMove();
		else
			valid = false;
	}

	return valid;
}

/**********************************************************************	
* Purpose: calls strtok on move
*
* Entry: Nothing is passed into this function
*
* Exit: If move can not be tokenized further, false is returned
*		If it can, it is and true is returned
*
************************************************************************/
bool GameBoard::tokenize()
{
	bool m_move = true;

	tok = strtok(NULL, " ");

	if (tok == nullptr)
		m_move = false;

	return m_move;
}

/**********************************************************************	
* Purpose: Validates the move from the p_area and moves the card(s) to the
*		   designated position
*
* Entry: Nothing is passed into this function
*
* Exit: Either a card(s) is moved from p_area or an error is printed
*		Nothing is returned
*
************************************************************************/
bool GameBoard::checkPMove()
{
	bool valid = true;
	Card temp;
	int row;
	int column;
	int dest_col;

	valid = tokenize();

	if (valid)
	{
		row = (int)(*tok);

		if (row >= 65 && row <= 90)
			row = row - 65;
		else if (row >= 97 && row <= 122)
			row = row - 97;
		else 
			valid = false;

		valid = tokenize();

		if (valid)
		{
			column = atoi(tok);
			valid = tokenize();

			if (valid && (*tok == 'H' || *tok == 'h'))
			{
				try
				{
					temp = p_area.GetSingleCard(column, row);

					try
					{
						h_area.MoveCard(temp);
					}
					catch (Exception & except)
					{
						p_area.undo(temp, column);
						cout << except << endl;
						valid = false;
					}
				}
				catch (Exception & except)
				{
					cout << except << endl;
					valid = false;
				}
			}
			else if (valid && (*tok == 'F' || *tok == 'f'))
			{
				try
				{
					temp = p_area.GetSingleCard(column, row);
				
					valid = tokenize();

					if (valid)
					{
						dest_col = atoi(tok);

						try 
						{
							f_area.PlaceCard(temp, dest_col);
						}
						catch (Exception & except)
						{
							p_area.undo(temp, column);
							cout << except << endl;
							valid = false;
						}
					}
					else
					{
						cout << "Please enter a valid move" << endl;
						p_area.undo(temp, column);
					}
				}
				catch (Exception & except)
				{
					cout << except << endl;
					valid = false;
				}
			}
			else if (valid && (*tok == 'P' || *tok == 'p'))
			{
				valid = tokenize();

				if (valid)
				{
					dest_col = atoi(tok);

					try
					{
						p_area.MoveCards(column, row, f_area.getNumOfEmptyCells(), dest_col);
					}
					catch (Exception & except)
					{
						cout << except << endl;
						valid = false;
					}
				}
			}
		}
	}

	return valid;
}

/**********************************************************************	
* Purpose: Validates the move from the f_area and moves the card to the
*		   designated position
*
* Entry: Nothing is passed into this function
*
* Exit: Either a card is moved from f_area or an error is printed
*		Nothing is returned
*
************************************************************************/
bool GameBoard::checkFMove()
{
	bool valid = true;
	Card temp;
	int free_cell;
	int dest_col;

	valid = tokenize();

	if (valid)
	{
		free_cell = atoi(tok);

		if (free_cell >= 0 && free_cell < 4)
		{
			valid = tokenize();

			try
			{
				temp = f_area.RemoveCard(free_cell);
			}
			catch (Exception & except)
			{
				cout << except << endl;
				valid = false;
			}

			if (valid && (*tok == 'P' || *tok == 'p'))
			{
				valid = tokenize();

				if (valid)
				{
					dest_col = atoi(tok);

					if (dest_col >= 0 && dest_col <= 7)
					{
						try
						{
							p_area.MoveCard(temp, dest_col);
						}
						catch (Exception & except)
						{
							cout << except << endl;
							f_area.PlaceCard(temp, free_cell);
							valid = false;
						}
					}
					else 
					{
						valid = false;
						f_area.PlaceCard(temp, free_cell);
					}
				}
				else 
				{
					f_area.PlaceCard(temp, free_cell);
				}
			}
			else if (valid && (*tok == 'H' || *tok == 'h'))
			{
				try
				{
					h_area.MoveCard(temp);
				}
				catch (Exception & except)
				{
					cout << except << endl;
					f_area.PlaceCard(temp, free_cell);
					valid = false;
				}
			}	
			else if (valid && (*tok == 'F' || *tok == 'f'))
			{
				valid = tokenize();

				if (valid)
				{
					dest_col = atoi(tok);

					if (dest_col >= 0 && dest_col < 4)
					{
						try 
						{
							f_area.PlaceCard(temp, dest_col);
						}
						catch (Exception &except)
						{
							cout << except << endl;
							f_area.PlaceCard(temp, free_cell);
							valid = false;
						}
					}
					else 
					{
						f_area.PlaceCard(temp, free_cell);
					}
				}
				else 
				{
					f_area.PlaceCard(temp, free_cell);
				}
			}
			else
			{
				f_area.PlaceCard(temp, free_cell);
			}
		}
		else 
			valid = false;
	}

	return valid;
}

/**********************************************************************	
* Purpose: Prints the specifications of how the moves should be entered	   
*
* Entry: Nothing is passed to this function
*
* Exit: Nothing is returned
*
************************************************************************/
void GameBoard::printInstructions()
{
	system("cls");
	cout << "Moves must be entered in the format with spaces between each character:" << endl 
		 << "area card is to be moved from - 'p' or 'f'" << endl 
		 << "position1 <row> - only needed if moving from the play area" << endl
		 << "position2 <column>" << endl 
		 << "area card to be moved to - 'p', 'f', or 'h'" << endl 
		 << "position <column> - only needed if moving to the play area or free cells" << endl;
	cout << "Such as: P A 5 p 6, F 4 P 5, or P A 5 H" << endl;
}

/**********************************************************************	
* Purpose: Runs through all the cards at the top of the stacks in p_area
*		   as well as all the cards in f_area to see if they should be
*		   moved to h_area
*
* Entry: Nothing is passed to this function
*
* Exit: Nothing is returned
*
************************************************************************/
void GameBoard::checkCTHome()
{
	bool run = true;
	bool p_run;
	bool f_run;

	while (run)
	{
		run = false;
		p_run = false;
		f_run = false;
		for (int i = 0; i < NUMOFPLAYCOLUMNS; i++)
		{
			const Card * temp = nullptr;
			temp = p_area.ReferenceCard(i);

			if (temp != nullptr)
			{
				p_run = h_area.CheckAutoAdd(temp);

				if (p_run)
				{
					run = true;
					Card nTemp = p_area.GetSingleCard(i);
					h_area.MoveCard(nTemp);
				}
			}
		}

		for (int i = 0; i < NUMOFFREECELLS; i++)
		{
			const Card * temp = nullptr;
			temp = f_area.ReferenceCard(i);

			if (temp != nullptr)
			{
				f_run = h_area.CheckAutoAdd(temp);

				if (f_run)
				{
					run = true;
					Card nTemp = f_area.RemoveCard(i);
					h_area.MoveCard(nTemp);
				}
			}
		}
	}

}

#endif
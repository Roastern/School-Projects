/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 3
* Filename:			PlayArea.h
* Date Created:		4/29/2014
* Modifications:	
*
************************************************************/

#ifndef PLAYAREA_H_
#define PLAYAREA_H

#include "Deck.h"
#include "LStack.h"

//constant number of columns in the play area
const int NUMOFPLAYCOLUMNS = 8;

/************************************************************************
* Class: PlayArea
*
* Purpose: Stores an array of stacks of cards
*
* Manager functions:	
* 	PlayArea ( )
* 		Initiates the Array of stacks to be of size NUMOFPLAYCOLUMNS
*	PlayArea (const PlayArea & copy)
*		Creates a copy of the copy PlayArea
*	operator = (const PlayArea & copy)
*		Copies the Array of stacks from copy into the current PlayArea
*	~PlayArea ( )
*		deletes the Array of stacks
*
* Methods:		
*	PrintPlayArea ( )
*		Prints the cards stored in the array of stacks
*	MoveCards (int column, int pos, int free_cells, int dest_col)
*		Places a stack of cards designated by the column and pos into the
*		given destination column
*	MoveCard (Card nCard, int column)
*		Places the given card onto the stack designated by the column
*	GetSingleCard (int column, int pos)
*		Returns the card at the given position within the array of stacks
*	GetSingleCard (int column)
*		Returns the card at the top of the given stack
*	ReferenceCard(int column)
*		Returns a constant pointer to the card at the top of the given stack
*	undo (Card nCard, int column)
*		Places a card back onto the top of the given stack, disregarding
*		the FreeCell rules for where cards can be moved
*	isMoveValid(int column, int pos, int free_cells, int dest_col)
*		places the designated stack of cards into t_stack and checks whether
*		or not they are in the correct order to be moved
*	isMoveValid(int column)
*		checks to see if t_stack can be placed on the given column
*	isMoveValid(int column, int pos)
*		checks to see if the given card can be removed from the given stack
*	isMoveValid(Card & nCard, int column)
*		checks to see if the given card can be placed onto the given stack
*	stackToTemp(int column, int pos, int movable_cards)
*		places the given stack of cards into t_stack
*	tempToStack(int column)
*		places t_stack onto the given stack
*	populatePlayArea()
*		Populates the play area with cards from the Deck class
*************************************************************************/
class PlayArea
{
public:
	PlayArea();
	PlayArea(int seed);
	PlayArea(const PlayArea & copy);
	PlayArea & operator= (const PlayArea & copy);
	~PlayArea();

	void PrintPlayArea() const;

	void MoveCards(int column, int pos, int free_cells, int dest_col);
	void MoveCard(Card nCard, int column);
	const Card GetSingleCard(int column, int pos);
	const Card GetSingleCard(int column);
	const Card * ReferenceCard(int column);
	void undo(Card nCard, int column);

private:
	//if the stack of cards player wants moved is in the right order, calls second move validator
	bool isMoveValid(int column, int pos, int free_cells, int dest_col);
	//checks to see if the destination stack can hold the stack of cards to be moved
	bool isMoveValid(int column);
	//for moving a single card to home/freespace
	bool isMoveValid(int column, int pos) const;
	//for moving a card from free to play
	bool isMoveValid(Card & nCard, int column);

	bool stackToTemp(int column, int pos, int movable_cards);
	void tempToStack(int column);

	void populatePlayArea();

	Array<LStack<Card>> p_stack;
	LStack<Card> t_stack;
	Deck play_deck;
	int num_of_cards;

};

#endif
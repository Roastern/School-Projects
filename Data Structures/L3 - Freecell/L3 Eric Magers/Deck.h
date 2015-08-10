/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 3
* Filename:			Deck.h
* Date Created:		4/25/2014
* Modifications:	
*
************************************************************/

#ifndef DECK_H_
#define DECK_H_

#include "Card.h"
#include "Array.h"

//constant size of the deck of cards
const int DECKSIZE = 52;
//constant number of suits in the deck
const int NUMOFSUITS = 4;
//constant size of each suit in the deck
const int SUITSIZE = 13;

/************************************************************************
* Class: Deck
*
* Purpose: Creates a Deck of Cards
*
* Manager functions:	
* 	Deck ( )
* 		Creates a deck of cards
*	Deck (int seed)
*		Creates a Card with the given seed value for srand()
*	Deck (const Deck & copy)
*		Creates a copy of the copy Deck
*	operator = (const Deck & copy)
*		Copies the deck of cards from copy into the current deck
*	~Deck()
*		deletes the deck of cards
*
* Methods:		
*	getCard ( )
*		Returns a card specified by the get_counter variable
*	shuffle ( )
*		Shuffles the deck of cards
*	fillDeck ( )
*		Fills the deck with all the cards in a normal card deck
*		
*************************************************************************/

class Deck
{
public:
	Deck();
	Deck(int seed);
	Deck(const Deck & copy);
	Deck & operator= (const Deck & copy);
	~Deck();

	const Card getCard();
	void shuffle();

private:
	Array<Card> c_deck;
	int get_counter;
	void fillDeck();
};













#endif
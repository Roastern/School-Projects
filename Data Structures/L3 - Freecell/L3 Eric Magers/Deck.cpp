/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 3
* Filename:			Deck.cpp
* Date Created:		4/25/2014
* Modifications:	
*
************************************************************/

#ifndef DECK_CPP_
#define DECK_CPP_

#include <stdlib.h>
#include <time.h>  
#include "Deck.h"

/**********************************************************************	
* Purpose: Initializes the deck to the default size and with a random
*		   seed for srand()
*
* Entry: No values are passed to this function
*
* Exit: Nothing is returned
*
************************************************************************/
Deck::Deck() : c_deck(DECKSIZE, 1), get_counter(1)
{
	srand (time(NULL));
	fillDeck();
	shuffle();
}

/**********************************************************************	
* Purpose: Initializes the deck with the given seed value for srand()
*
* Entry: No values are passed to this function
*
* Exit: Nothing is returned
*
************************************************************************/
Deck::Deck(int seed) : c_deck(DECKSIZE, 1), get_counter(1)
{
	srand (seed);
	fillDeck();
	shuffle();
}

/**********************************************************************	
* Purpose: Initializes a new deck to have the same cards in the same 
*		   position as another deck
*
* Entry: copy is the deck to be copied
*
* Exit: Nothing is returned
*
************************************************************************/
Deck::Deck(const Deck & copy) : get_counter(copy.get_counter)
{
	srand (time(NULL));
	c_deck = copy.c_deck;
}

/**********************************************************************	
* Purpose: Copies one deck into another
*
* Entry: copy is the Deck to be copied
*
* Exit: The current deck is returned
*
************************************************************************/
Deck & Deck::operator= (const Deck & copy)
{
	c_deck = copy.c_deck;
	get_counter = copy.get_counter;

	return *this;
}

/**********************************************************************	
* Purpose: Destroys the deck object
*
* Entry: No values are passed to this function
*
* Exit: Nothing is returned
*
************************************************************************/
Deck::~Deck()
{

}

/**********************************************************************	
* Purpose: Returns a card from the deck
*
* Entry: No values are passed to this function
*
* Exit: A card is returned, and get_counter is incremented so the next
*		call to this function will return the next card in the deck
*
************************************************************************/
const Card Deck::getCard()
{
	Card ret = c_deck[get_counter];
	get_counter++;

	return ret;
}

/**********************************************************************	
* Purpose: Shuffles the cards in the deck
*
* Entry: No values are passed to this function
*
* Exit: Nothing is returned
*
************************************************************************/
void Deck::shuffle()
{
	int random;
	Card temp;

	for (int i = 1; i <= DECKSIZE; i++)
	{
		random = rand() % DECKSIZE + 1;
		temp = c_deck[i];
		c_deck[i] = c_deck[random];
		c_deck[random] = temp;
	}

	get_counter = 1;
}

/**********************************************************************	
* Purpose: Fills the deck with all the cards that should be in a deck
*
* Entry: No values are passed to this function
*
* Exit: Nothing is returned
*
************************************************************************/
void Deck::fillDeck()
{
	for (int i = 0; i < NUMOFSUITS; i++)
	{
		for (int j = 0; j < SUITSIZE; j++)
		{
			Card * newCard = new Card((i + 1), (j + 1));

			c_deck[((i * SUITSIZE) + j) + 1] = *newCard;

			delete newCard;
		}
	}
}

#endif
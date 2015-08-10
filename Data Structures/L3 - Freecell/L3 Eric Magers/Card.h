/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 3
* Filename:			Cards.h
* Date Created:		4/25/2014
* Modifications:	
*
************************************************************/

#ifndef CARD_H_
#define CARD_H_

#include <iostream>
using std::ostream;

/************************************************************************
* Class: Card
*
* Purpose: Creates a Card data type
*
* Manager functions:	
* 	Card ( )
* 		Creates a Card with the value and suit set to 0	
*	Card (int nSuit, int nValue)
*		Creates a Card with the given values for suit and value
*	Card (const Card & copy)
*		Creates a copy of the copy Card
*	operator = (const Card & copy)
*		Copies the suit and value of the copy Card and stores it in the
*		current card
*	~Card()
*		deletes the Card
*
* Methods:		
*	operator<< (ostream & out, const Card & aCard)
*		Prints the given card to the given output stream
*	getSuit ( ) const
*		Returns the suit of the card
*	getCard_F ( ) const
*		Returns the face value of the card
*	setSuit (int nSuit)
*		Sets the suit to be the given value
*	setCard_F (int nValue)
*		Sets the cards face value to the given value
*		
*************************************************************************/

class Card
{
public:
	Card();
	Card(int nSuit, int nValue);
	Card(const Card & copy);
	Card & operator= (const Card & copy);
	~Card();

	friend ostream & operator<< (ostream & out, const Card & aCard);

	int getSuit() const;
	int getCard_F() const;
	void setSuit(int nSuit);
	void setCard_F(int nValue);

private:
	int suit;
	int card_face;

};

bool operator== (const Card & card1, const Card & card2);

#endif
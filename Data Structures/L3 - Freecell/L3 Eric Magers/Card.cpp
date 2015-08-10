/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Lab 3
* Filename:			Cards.cpp
* Date Created:		4/25/2014
* Modifications:	
*
************************************************************/

#ifndef CARD_CPP_
#define CARD_CPP_

#include <windows.h>
#include <iostream>
#include "Card.h"
#include "Exception.h"
using std::cout;
using std::endl;

HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
const int DEFAULT = 7;

/**********************************************************************	
* Purpose: Default constructor, initializes the card to null values
*
* Entry: No values are passed to this function
*
* Exit: A Card object is created
*
************************************************************************/
Card::Card() : suit(0), card_face(0)
{

}

/**********************************************************************	
* Purpose: initializes the card to the given suit and face value values
*
* Entry: nSuit is the value to be stored in suit, nValue is the value 
*		 to be stored in card_face
*
* Exit: A Card object is created
*
************************************************************************/
Card::Card(int nSuit, int nValue) : suit(nSuit), card_face(nValue)
{

}

/**********************************************************************	
* Purpose: initializes the card to the suit and face value values
*		   which are stored in copy
*
* Entry: copy is the card which the new card is initialized from
*
* Exit: A Card object is created
*
************************************************************************/
Card::Card(const Card & copy) : suit(copy.suit), card_face(copy.card_face)
{

}

/**********************************************************************	
* Purpose: initializes the card to the suit and face value values
*		   which are stored in copy
*
* Entry: copy is the card which the new card is initialized from
*
* Exit: The current Card is returned
*
************************************************************************/
Card & Card::operator= (const Card & copy)
{
	suit = copy.getSuit();
	card_face = copy.getCard_F();

	return *this;
}

/**********************************************************************	
* Purpose: Destroys the card object
*
* Entry: No values are passed into this function
*
* Exit: The Card is destroyed
*
************************************************************************/
Card::~Card()
{

}

/**********************************************************************	
* Purpose: Prints the specified card object
*
* Entry: out is the output stream to be printed to, aCard is the address
*			of the card to be printed
*
* Exit: aCard is printed to out
*
************************************************************************/
ostream & operator<< (ostream & out, const Card & aCard)
{
	int textColor = 240;

	//if the suit is a ^ or *, then print in red text
	if (aCard.suit > 2)
		textColor = 252;

	SetConsoleTextAttribute(handle, textColor);

	//prints the card's value
	switch (aCard.card_face)
	{
	case 1:
		cout << "A";
		break;
	case 11:
		cout << "J";
		break;
	case 12:
		cout << "Q";
		break;
	case 13:
		cout << "K";
		break;
	default:
		cout << aCard.card_face;
	}

	//prints the cards face, @ = spade, # = club, ^ = diamond, * = heart
	switch (aCard.suit)
	{
	case 1:
		cout << "@";
		break;
	case 2:
		cout << "#";
		break;
	case 3:
		cout << "^";
		break;
	case 4: 
		cout << "*";
		break;
	default:
		cout << "OOPS... Something bad happened";
	}

	SetConsoleTextAttribute(handle, DEFAULT);

	return out;
}

/**********************************************************************	
* Purpose: Returns the value stored in suit
*
* Entry: No values are passed to this function
*
* Exit: suit is returned
*
************************************************************************/
int Card::getSuit() const
{
	return suit;
}

/**********************************************************************	
* Purpose: Returns the value stored in card_face
*
* Entry: No values are passed to this function
*
* Exit: card_face is returned
*
************************************************************************/
int Card::getCard_F() const
{
	return card_face;
}

/**********************************************************************	
* Purpose: Sets the value of suit
*
* Entry: nSuit is the value to be stored in suit
*
* Exit: suit is set to nSuit, no values are returned
*
************************************************************************/
void Card::setSuit(int nSuit)
{
	if (nSuit > 4 || nSuit < 0)
		throw Exception("The suit value you entered is invalid");

	suit = nSuit;
}

/**********************************************************************	
* Purpose: Sets the value of card_face
*
* Entry: card_face is the value to be stored in suit
*
* Exit: suit is set to card_face, no values are returned
*
************************************************************************/
void Card::setCard_F(int nValue)
{
	if (nValue > 13 || nValue < 1)
		throw Exception("The card value you entered is invalue");

	card_face = nValue;
}

/**********************************************************************	
* Purpose: Determines whether or not the two given cards are equal to 
*		   each other
*
* Entry: card1 and card2 are the two Card objects to be compared
*
* Exit: true is returned if the two cards are identical, false is returned
*		if not
*
************************************************************************/
bool operator== (const Card & card1, const Card & card2)
{
	bool equals = false;

	if (card1.getSuit() == card2.getSuit() && card1.getCard_F() == card2.getCard_F())
		equals = true;
	
	return equals;
}
#endif
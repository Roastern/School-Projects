#ifndef HOMECELLAREA_CPP_
#define HOMECELLAREA_CPP_

#include "HomeCellArea.h"

/**********************************************************************	
* Purpose: Initializes h_cells, the array of stacks of cards
*		   to be of size NUMOFHOMECOLUMNS
*
* Entry: Nothing is passed to this function
*
* Exit: Nothing is returned
*
************************************************************************/
HomeCellArea::HomeCellArea() : h_cells(NUMOFHOMECOLUMNS)
{

}

/**********************************************************************	
* Purpose: Copies the array of stacks stored in copy into a new 
*		   HomeCellArea object
*
* Entry: copy is the HomeCellArea to be copied
*
* Exit: Nothing is returned
*
************************************************************************/
HomeCellArea::HomeCellArea(const HomeCellArea & copy) : h_cells(copy.h_cells)
{

}

/**********************************************************************	
* Purpose: Copies the array of stacks stored in copy into the current
*		   HomeCellArea
*
* Entry: copy is the HomeCellArea to be copied
*
* Exit: The current HomeCellArea is returned
*
************************************************************************/
HomeCellArea & HomeCellArea::operator= (const HomeCellArea & copy)
{
	if (this != &copy)
	{
		h_cells = copy.h_cells;
	}

	return *this;
}

/**********************************************************************	
* Purpose: Deletes the array of stacks of cards
*
* Entry: Nothing is passed into this function
*
* Exit: Nothing is returned
*
************************************************************************/
HomeCellArea::~HomeCellArea()
{

}

/**********************************************************************	
* Purpose: Prints the cards at the top of the stacks in each HomeCellArea
*		   column
*
* Entry: Nothing is passed to this function
*
* Exit: Nothing is returned
*
************************************************************************/
void HomeCellArea::PrintHomeArea() const
{
	for (int i = 0; i < NUMOFHOMECOLUMNS; i++)
	{
		if (!(h_cells[i].isEmpty()))
		{
			if (h_cells[i].Peek().getCard_F() == 10)
				cout << h_cells[i].Peek() << " ";
			else 
				cout << h_cells[i].Peek() << "  ";
		}
		else
			cout << "   ";
	}
}

/**********************************************************************	
* Purpose: Places the given card into the column specified by isMoveValid
*		   or throws an exception of not possible
*
* Entry: nCard is the card to be placed in the home area
*
* Exit: nCard is placed in the home area or an exception is thrown
*		Nothing is returned
*
************************************************************************/
void HomeCellArea::MoveCard(const Card & nCard)
{
	int column = isMoveValid(nCard);

	if (column == NUMOFHOMECOLUMNS)
		throw Exception("Cannot move this card to the home area");
	
	h_cells[column].Push(nCard);
}

/**********************************************************************	
* Purpose: Checks to see if the given card can be placed into any of 
*		   the home area stacks
*
* Entry: nCard is the card to be added to the stacks
*
* Exit: the position of the stack in which the card can be placed 
*       within the h_cells array is returned
*	    If the card can not be placed in any stack, NUMOFHOMECOLUMNS
*		is returned by default
*
************************************************************************/
int HomeCellArea::isMoveValid(const Card & nCard)
{
	bool found = false;
	int column = NUMOFHOMECOLUMNS;
	Card temp;

	if (nCard.getCard_F() == 1)
	{
		for (int i = 0; i < NUMOFHOMECOLUMNS && !found; i++)
		{
			if (h_cells[i].isEmpty())
			{
				column = i;
				found = true;
			}
		}
	}
	else
	{
		for (int i = 0; i < NUMOFHOMECOLUMNS && !found; i++)
		{
			if (h_cells[i].isEmpty())
				found = false;
			else
			{
				temp = h_cells[i].Peek();
				if (nCard.getCard_F() == temp.getCard_F() + 1)
				{
					if (nCard.getSuit() == temp.getSuit())
					{
						found = true;
						column = i;
					}
				}
			}
		}
	}

	return column;
}

/**********************************************************************	
* Purpose: Checks to see if the the home area stacks are full
*
* Entry: Nothing is passed into the function
*
* Exit: True is returned if all home stacks are full
*		False is returned if the stacks are not full
*
************************************************************************/
bool HomeCellArea::isWin() const
{
	bool hasWon = true;

	for (int i = 0; i < NUMOFHOMECOLUMNS && hasWon; i++)
	{
		if (!(h_cells[i].isEmpty()))
		{
			if (h_cells[i].Peek().getCard_F() != 13)
			{
				hasWon = false;
			}
		}
		else 
			hasWon = false;
	}

	return hasWon;
}

/**********************************************************************	
* Purpose: Checks to see if the given card can automatically be placed
*		   in the home area
*
* Entry: nCard is the card which is to be placed in the home area
*
* Exit: True is returned if a card can be placed in the home area
*		False is returned if the card can not
*
************************************************************************/
bool HomeCellArea::CheckAutoAdd(const Card * nCard)
{
	int add = isMoveValid(*nCard);
	bool add_card = false; 

	if (nCard->getCard_F() == 1)
	{
		add_card = true;
	}
	else if (nCard->getCard_F() == 2 && add != NUMOFHOMECOLUMNS)
	{
		add_card = true;
	}
	else if (add != NUMOFHOMECOLUMNS)
	{
		add = 0;
		for (int i = 0; i < NUMOFHOMECOLUMNS; i++)
		{
			if (!h_cells[i].isEmpty())
			{
				if (nCard->getSuit() <= 2 && h_cells[i].Peek().getSuit() >= 3)
				{
					if (h_cells[i].Peek().getCard_F() >= (nCard->getCard_F() - 1))
						add++;
				}
				else if (nCard->getSuit() >= 3 && h_cells[i].Peek().getSuit() <= 2)
				{
					if (h_cells[i].Peek().getCard_F() >= (nCard->getCard_F() - 1)) 
						add++;
				}
			}
		}
	}

	if (add == 2)
		add_card = true;

	return add_card;
}
#endif
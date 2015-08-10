#ifndef PLAYAREA_CPP_
#define PLAYAREA_CPP_

#include <math.h>
#include "PlayArea.h"
using std::pow;

/**********************************************************************	
* Purpose: Initializes p_stack, the array of stacks to be of size
*		   NUMOFPLAYCOLUMNS, populates p_stack with cards from play_deck
*
* Entry: Nothing is passed to this function
*
* Exit: Nothing is returned
*
************************************************************************/
PlayArea::PlayArea() : p_stack(NUMOFPLAYCOLUMNS), t_stack(), 
					   play_deck(), num_of_cards(DECKSIZE)
{
	populatePlayArea();
}

/**********************************************************************	
* Purpose: Initializes p_stack, the array of stacks to be of size
*		   NUMOFPLAYCOLUMNS, populates p_stack with cards from play_deck
*		   play_deck is initialized with the given seed
*
* Entry: Nothing is passed to this function
*
* Exit: Nothing is returned
*
************************************************************************/
PlayArea::PlayArea(int seed) : p_stack(NUMOFPLAYCOLUMNS), t_stack(), play_deck(seed),
							   num_of_cards(DECKSIZE)
{
	populatePlayArea();
}

/**********************************************************************	
* Purpose: Initializes the values of the new PlayArea to be the same
*		   as the values stored in copy
*
* Entry: copy is the PlayArea to be copied
*
* Exit: Nothing is returned
*
************************************************************************/
PlayArea::PlayArea(const PlayArea & copy) : p_stack(copy.p_stack), t_stack(copy.t_stack),
											play_deck(copy.play_deck),
											num_of_cards(DECKSIZE)
{

}

/**********************************************************************	
* Purpose: Copies the values stored in copy into the current PlayArea
*		   object
*
* Entry: copy is the PlayArea to be copied
*
* Exit: The current object is returned
*
************************************************************************/
PlayArea & PlayArea::operator= (const PlayArea & copy) 
{
	if (this != &copy)
	{
		p_stack = copy.p_stack;
		t_stack = copy.t_stack;
		play_deck = copy.play_deck;
		num_of_cards = copy.num_of_cards;
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
PlayArea::~PlayArea()
{

}

/**********************************************************************	
* Purpose: Populates the array of stacks of cards with cards from the
*		   play_deck
*
* Entry: Nothing is passed into this function
*
* Exit: Nothing is returned
*
************************************************************************/
void PlayArea::populatePlayArea()
{
	int numOfCards = 0;

	while (numOfCards < DECKSIZE)
	{
		for (int j = 0; j < NUMOFPLAYCOLUMNS; j++)
		{
			if (numOfCards < DECKSIZE)
			{
				p_stack[j].Push(play_deck.getCard());
				numOfCards++;
			}
		}
	}
}

/**********************************************************************	
* Purpose: Prints the p_stack array
*
* Entry: Nothing is passed into this function
*
* Exit: Nothing is returned
*
************************************************************************/
void PlayArea::PrintPlayArea() const 
{
	Array<LStack<Card>> tempArea(8);
	int numOfCards = 0;
	char letterHead = 'A';

	//populates tempArea;
	for (int i = 0; i < NUMOFPLAYCOLUMNS; i++)
	{
		int size = p_stack[i].Size();
		for (int j = 0; j < size; j++)
		{
			tempArea[i].Push(p_stack[i].Pop());
		}
	}

	cout << "   ";
	for (int i = 0; i < NUMOFPLAYCOLUMNS; i++)
	{
		cout << i << "   ";
	}

	cout << endl;

	//prints p_stack
	while (numOfCards < num_of_cards)
	{
		cout << letterHead << "  ";
		for (int j = 0; j < NUMOFPLAYCOLUMNS; j++)
		{
			if (tempArea[j].Size() != 0)
			{
				p_stack[j].Push(tempArea[j].Pop());

				if (p_stack[j].Peek().getCard_F() == 10)
					cout << p_stack[j].Peek() << " ";
				else
					cout << p_stack[j].Peek() << "  ";
				numOfCards++;
			}
			else 
				cout << "    ";
		}
		letterHead++;
		cout << endl;
	}
	cout << endl;
}

/**********************************************************************	
* Purpose: Moves the designated stack of cards to a different column
*		   within PlayArea
*
* Entry: Nothing is passed into this function
*
* Exit: Nothing is returned
*
************************************************************************/
void PlayArea::MoveCards(int column, int pos, int free_cells, int dest_col)
{
	bool valid_move = isMoveValid(column, pos, free_cells, dest_col);

	if (valid_move)
	{
		tempToStack(dest_col);
	}
	else
	{
		tempToStack(column);
		cout << "That move cannot be made" << endl;
	}
}

/**********************************************************************	
* Purpose: Moves the given card onto the given stack
*
* Entry: nCard is the card to be placed into the play area
*		 column is the array index of the stack where the card is to be
*		 placed
*
* Exit: Nothing is returned
*
************************************************************************/
void PlayArea::MoveCard(Card nCard, int column)
{
	if (!(isMoveValid(nCard, column)))
		throw Exception("Cannot place the card in the specified column");

	p_stack[column].Push(nCard);
	num_of_cards++;
}

/**********************************************************************	
* Purpose: Checks to see if t_stack can be placed onto the designated 
*		   play column
*
* Entry: column is the index of the array where the stack is to be moved from
*		 pos is the number of cards from the column to be moved
*		 free_cells is the number of free cells available
*		 dest_col is the column where the stack is to be moved to
*
* Exit: True is returned if the stack can be moved
*		False is returned if it cannot
*
************************************************************************/
bool PlayArea::isMoveValid(int column, int pos, int free_cells, int dest_col)
{
	bool valid_move = true;
	int movableCards;
    int free_columns = 0;

    for (int i = 0; i < NUMOFPLAYCOLUMNS; i++)
	{
        if (p_stack[i].isEmpty())
            free_columns++;
	}

	if (p_stack[column].isEmpty())
	{
		valid_move = false;
		cout << "There are no cards to be moved at the specified location." << endl;
	}
	else if (p_stack[column].Size() < pos)
	{
		valid_move = false;
		cout << "There are no cards to be moved at the specified location." << endl;
	}
	else
	{
		if (p_stack[dest_col].isEmpty())
			movableCards = pow(2, free_columns - 1) + free_cells;
		else
			movableCards = pow(2, free_columns) + free_cells;

		valid_move = stackToTemp(column, pos, movableCards);

		int difference = movableCards - t_stack.Size();

		if (difference < 0 && t_stack.Size() != 1)
		{
			valid_move = false;
			cout << "You need room to move " << (-1)*difference 
				 << " more card(s) to make that move" << endl;
		}
		else if (p_stack[dest_col].isEmpty() && valid_move)
		{
			valid_move = true;
		}
		else
		{
			if (valid_move)
			{
				const Card & temp_t = t_stack.Peek();
				const Card & temp_c = p_stack[dest_col].Peek();

				if (temp_t.getCard_F() == temp_c.getCard_F() - 1)
				{
					if (temp_t.getSuit() > 2 && temp_c.getSuit() < 3)
						valid_move = true;
					else if (temp_t.getSuit() < 3 && temp_c.getSuit() > 2)
						valid_move = true;
					else 
					{
						cout << "Cannot move the stack of cards to the specified column" << endl;
						valid_move = false;
					}
				}
				else
					valid_move = false;
			}
		}
	}

	return valid_move;
}

/**********************************************************************	
* Purpose: Removes a single card from the given stack
*
* Entry: column is the index of the stack where the card is to be removed
*		 pos is the position on the stack where the card is to be removed
*
* Exit: The card which was removed from the stack is returned
*
************************************************************************/
const Card PlayArea::GetSingleCard(int column, int pos)
{
	bool moved = isMoveValid(column, pos);
	Card r_card;

	if (!moved)
	{
		throw Exception("The card you specified cannot be retrieved");
	}

	r_card = p_stack[column].Pop();

	num_of_cards--;

	return r_card;
}

/**********************************************************************	
* Purpose: Removes a single card from the given stack
*
* Entry: column is the index of the stack where the card is to be removed
*
* Exit: The card which was removed from the stack is returned
*
************************************************************************/
const Card PlayArea::GetSingleCard(int column)
{
	Card r_card = Card();

	if (column <= 7 && column >= 0)
	{
		if (!(p_stack[column].isEmpty()))
		{
			r_card = p_stack[column].Pop();
		}
	}

	num_of_cards--;

	return r_card;
}

/**********************************************************************	
* Purpose: Checks to see if a single card can be removed from the given
*		   stack
*
* Entry: column is the index of the stack where the card is to be removed
*		 pos is the position on the stack where the card is to be removed
*
* Exit: true is returned if a card can be removed
*		false is returned if not
*
************************************************************************/
bool PlayArea::isMoveValid(int column, int pos) const
{
	bool valid = false;

	if (!(p_stack[column].isEmpty()) && (p_stack[column].Size() - 1) == pos)
		valid = true;

	return valid;
}

/**********************************************************************	
* Purpose: Checks to see if a single card can be added to the given 
*		   stack
*
* Entry: column is the index of the stack where the card is to be added
*		 nCard is the card to be added to the stack
*
* Exit: True is returned if the card can be added
*		false is returned if it cannot
*
************************************************************************/
bool PlayArea::isMoveValid(Card & nCard, int column)
{
	bool valid = false;

	if (p_stack[column].isEmpty())
	{
		valid = true;
	}
	else 
	{
		Card temp = p_stack[column].Peek();

		if (nCard.getCard_F() == temp.getCard_F() - 1)
		{
			if (nCard.getSuit() > 2 && temp.getSuit() < 3)
				valid = true;
			else if (nCard.getSuit() < 3 && temp.getSuit() > 2)
				valid = true;
			else 
			{
				cout << "Cannot move the stack of cards to the specified column" << endl;
				valid = false;
			}
		}
	}

	return valid;
}

/**********************************************************************	
* Purpose: Removes a stack of cards from the given stack and places it
*		   onto t_stack
*
* Entry: column is the index of the stack where the cards are to be removed
*		 pos is the position on the stack where the cards are to stop being
*		 removed
*		 moveable_cards is the number of cards which can be moved while following
*		 the rules of freecell
*
* Exit: true is returned if the stack of cards removed from p_stack are
*	    in order, following the rules of freecell
*		false is returned if they are not
*
************************************************************************/
bool PlayArea::stackToTemp(int column, int pos, int movable_cards)
{
	bool valid_move = true;
	Card temp;

	if (!p_stack[column].isEmpty())
	{
		t_stack.Push(p_stack[column].Pop());

		while (!p_stack[column].isEmpty() && p_stack[column].Size() > pos && valid_move)
		{
			temp = p_stack[column].Peek();

			if (temp.getSuit() >= 3 && t_stack.Peek().getSuit() <= 2 
				&& temp.getCard_F() == (t_stack.Peek().getCard_F() + 1))
			{
				t_stack.Push(p_stack[column].Pop());
			}
			else if (temp.getSuit() <= 2 && t_stack.Peek().getSuit() >= 3 
					 && temp.getCard_F() == (t_stack.Peek().getCard_F() + 1))
			{
				t_stack.Push(p_stack[column].Pop());
			}
			else
				valid_move = false;
		}
	}
	else 
		valid_move = false;

	return valid_move;			
}

/**********************************************************************	
* Purpose: Places t_stack onto the given p_stack
*
* Entry: column is the index of the stack where t_stack is to be placed
*
* Exit: t_stack is emptied onto p_stack
*
************************************************************************/
void PlayArea::tempToStack(int column)
{
	int size = t_stack.Size();

	for (int i = 0; i < size; i++)
		p_stack[column].Push(t_stack.Pop());
}

/**********************************************************************	
* Purpose: Places the given card back onto the stack it was removed from
*
* Entry: column is the index of the stack where the card is to be added
*		 nCard is the card to be placed back onto the stack
*
* Exit: nCard is added to the given stack
*
************************************************************************/
void PlayArea::undo(Card nCard, int column)
{
	p_stack[column].Push(nCard);
	num_of_cards++;
}

/**********************************************************************	
* Purpose: Returns a constant pointer to the card at the top of the 
*		   designated stack
*
* Entry: column is the index of the stack where the card is to be referenced
*
* Exit: A pointer to the designated card is returned
*
************************************************************************/
const Card * PlayArea::ReferenceCard(int column)
{
	const Card * temp = nullptr;

	if (!(p_stack[column].isEmpty()) && column >= 0 && column <= 7)
	{
		temp = &p_stack[column].Peek();
	}

	return temp;
}

#endif
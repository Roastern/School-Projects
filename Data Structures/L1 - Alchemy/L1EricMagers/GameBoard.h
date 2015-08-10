/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Assignment 2
* Filename:			GameBoard.h
* Date Created:		4/6/2014
* Modifications:	4/8/2014 – Added documentation
************************************************************/
#ifndef GAMEBOARD_H_
#define GAMEBOARD_H_

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "Array2D.h"
#include "Exception.h"
#include "Block.h"
using std::cin;
using std::cout;
using std::string;

/************************************************************************
* Class: GameBoard
*
* Purpose: This class creates a board of type Array2D<Block> and manipulates
*			this board following the rules of the game Alchemy
*
* Manager functions:	
* 	GameBoard ( )
* 		Initializes the m_board object to default values, fills the block
*			in the center of the board to free space
*	GameBoard (ostream & out_stream)
*		Initializes the Array2D object to default values, output stream is
*			set to out_stream
*	GameBoard (const GameBoard &copy)
*		Initializes the GameBoard to have the same values as the copy object
*	~GameBoard ( )
*		Deletes the GameBoard object
*	operator = (const GameBoard &rhs)
*		Copies rhs into the specified GameBoard object
*
* Public Methods:		
*	getMove ( )
*		Retrieves the move from user, then passes move to isMoveValid()
*			to be checked for validity. Continues to retrieve the users 
*			move until valid move is entered
*	printBoard ( )
*		Prints m_board along with column/row identifiers as well as the 
*			current score and number of discards
*	clearBoard ( )
*		Clears m_board of all Blocks and then places the free block in 
*			the middle of m_board
*	nextBlock ( )
*		Randomly generates the values for the next Block to be entered
*			into m_board, then stores them in m_block
*	getLevel ( )
*		Returns m_level
*	incLevel ( )
*		Increments the level by 1
*	getScore ( )
*		Returns m_score
*	getDiscard ( ) 
*		Returns m_discard
*	getEmptyBlocks ( )
*		Returns m_empty_blocks
*	getOutStream ( ) 
*		Returns stream
*Private Methods:
*	isMoveValid (const string move)
*		Converts move into two ints, row and column, and then tests these
*			values to make sure they fall within the bounds of m_board
*	checkMove (int row, int column)
*		Checks to see if the row and column position is valid for the 
*			for m_block to be input
*	placeBlock (int row, int column) 
*		Places m_block inside m_board
*	checkRowClear (int row)
*		Checks specified row to see if it is full
*	clearRow (int row)
*		Clears specified row of all symbols, color for all blocks within
*			is set to GOLD
*	checkColumnClear (int column)
*		Checks specified row to see if it is full
*	clearColumn (int column)
*		Clears specified row of all symbols, color for all blocks within
*			is set to GOLD
*	IntToColors (int color) 
*		Converts randomly generated number to the correct color value for
*			m_block
*	IntToSymbols (int symbol)
*		Converts randomly generated number to the correct color value for
*			m_block
*************************************************************************/

//default m_board dimensions
const int DEFAULT_BOARD_ROW = 8;
const int DEFAULT_BOARD_COLUMN = 9;

class GameBoard
{
public:
	GameBoard();
	GameBoard(ostream& out_stream);
	GameBoard(const GameBoard &copy);
	~GameBoard();

	GameBoard& operator= (const GameBoard &rhs);

	void getMove();
	void printBoard() const;
	void clearBoard();
	void nextBlock();

	int getLevel() const;
	void incLevel();
	int getScore() const;
	int getDiscard() const;
	int getEmptyBlocks() const;
	ostream& getOutStream() const;

private:
	Block m_block;
	int m_level;
	int m_score;
	int m_discard;
	int m_empty_blocks;

	Array2D<Block> m_board;
	ostream& stream;
	
	bool isMoveValid(const string move);
	bool checkMove(int row, int column);
	void placeBlock(int row, int column);
	void checkRowColumnClear(int row, int column);
	void clearRow(int row);
	void clearColumn(int column);

	int IntToColors(int color);
	char IntToSymbols(int symbol);
};

enum Colors {BLACK = 96, GOLD = 102, WHITE = 111, GRAY = 103, YELLOW = 110, RED = 108, GREEN = 106, BLUE = 105, PURPLE = 101, AQUA = 107, LPURPLE = 109, DEFAULT = 7};

#endif
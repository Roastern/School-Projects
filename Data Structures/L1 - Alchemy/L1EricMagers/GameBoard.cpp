/***********************************************************
* Author:			Eric Magers
* Lab Number:		CST 211 Assignment 2
* Filename:			GameBoard.cpp
* Date Created:		4/6/2014
* Modifications:	4/8/2014 – Added function documentation
*							 - Fixed bug allowing level completion to happen prematurely
*							 - Fixed bug causing crash when no value was input for move
*							 - Fixed bug that allowed free blocks to be placed anywhere
************************************************************/

#ifndef GAMEBOARD_CPP_
#define GAMEBOARD_CPP_

#include "GameBoard.h"

/**********************************************************************	
* Purpose: Default constructor, initializes GameBoard object with 
*			default values
*
* Entry: No values are entered
*
* Exit: m_board is initialized with default row and column sizes
*		m_level, m_score, m_discard are initialized with the value 0
*		m_empty_blocks is initialized with default size row * column
*		stream is initialized to cout
*
************************************************************************/
GameBoard::GameBoard() : m_board(DEFAULT_BOARD_ROW, DEFAULT_BOARD_COLUMN), m_level(0), m_score(0), m_discard(0), m_empty_blocks(DEFAULT_BOARD_ROW * DEFAULT_BOARD_COLUMN), stream(cout)
{
	srand(time(0));
	m_board[DEFAULT_BOARD_ROW/2][DEFAULT_BOARD_COLUMN/2].setFColor(GRAY);
	m_board[DEFAULT_BOARD_ROW/2][DEFAULT_BOARD_COLUMN/2].setSymbol('#');
}

/**********************************************************************	
* Purpose: Initializes GameBoard object with default values, sets output
*			to the specified value
*
* Entry: out_stream is the output stream that GameBoard will print to
*
* Exit: m_board is initialized with default row and column sizes
*		m_level, m_score, m_discard are initialized with the value 0
*		m_empty_blocks is initialized with default size row * column
*		stream is initialized to out_stream
*
************************************************************************/
GameBoard::GameBoard(ostream &out_stream) : m_board(DEFAULT_BOARD_ROW, DEFAULT_BOARD_COLUMN), m_level(0), m_score(0), m_discard(0), m_empty_blocks(DEFAULT_BOARD_ROW * DEFAULT_BOARD_COLUMN), stream(out_stream)
{
	srand(time(0));
	m_board[DEFAULT_BOARD_ROW/2][DEFAULT_BOARD_COLUMN/2].setFColor(GRAY);
	m_board[DEFAULT_BOARD_ROW/2][DEFAULT_BOARD_COLUMN/2].setSymbol('#');
}

/**********************************************************************	
* Purpose: Initializes a GameBoard object to have the same values as the
*			given object
*
* Entry: copy is the GameBoard object that is to be copied into the new object
*
* Exit: m_board is initialized to the same dimensions as copy's m_board
*		m_level, m_score, m_discard are initialized with the values as 
*			copy's as well as m_empty_blocks
*		stream is initialized to copy's stream
*
************************************************************************/
GameBoard::GameBoard(const GameBoard &copy) : m_board(DEFAULT_BOARD_ROW, DEFAULT_BOARD_COLUMN), m_level(copy.getLevel()), m_score(copy.getScore()), m_discard(copy.getDiscard()), m_empty_blocks(copy.getEmptyBlocks()), stream(copy.getOutStream())
{
	srand(time(0));
	m_board = copy.m_board;
}

/**********************************************************************	
* Purpose: Destroys the GameBoard object
*
* Entry: No values are passed into this function
*
* Exit: No values are returned
*
************************************************************************/
GameBoard::~GameBoard()
{

}

/**********************************************************************	
* Purpose: Copies the given GameBoard object into the current object
*
* Entry: rhs is the GameBoard object to be copied
*
* Exit: m_level, m_score, m_discard are initialized with the values as 
*		 copy's as well as m_empty_blocks
*		m_board is set equal to rhs's m_board
*
************************************************************************/
GameBoard& GameBoard::operator= (const GameBoard &rhs)
{
	m_level = rhs.getLevel();
	m_score = rhs.getScore();
	m_discard = rhs.getDiscard();
	m_empty_blocks = rhs.getEmptyBlocks();

	m_board = rhs.m_board;

	return *this;
}

/**********************************************************************	
* Purpose: Generates random values for m_block, then gets input from the
*			user to determine where they want the block placed on the board
*
* Entry: Calls nextBlock() to assign random values to m_block
*
* Exit: Retrieves a move from client, then determines it's validity by
*		 passing it to isMoveValid()
*		No value is returned
*
************************************************************************/
void GameBoard::getMove()
{
	bool move_made = false;
	nextBlock();
	string move;

	while (!move_made)
	{
		printBoard();
		stream << "Select the position to place " << m_block << endl;
		stream << "Must be in the format of (a-h)(1-9), such as c7 (dd to discard): ";

		getline(cin, move);
		stream << endl;

		system("cls");

		if (move != "")
		{
			try
			{
				move_made = isMoveValid(move);
			}
			catch (Exception &except)
			{
				stream << except  << endl;
			}
		}
	}
}

/**********************************************************************	
* Purpose: Prints the board
*
* Entry: No values are passed into this function
*
* Exit: No values are returned
*		The gameboard is printed along with the score and number of discards
*
************************************************************************/
void GameBoard::printBoard() const
{
	stream << "   0 1 2 3 4 5 6 7 8 " << endl;
	stream << "  ###################" << endl;
	for (int i = 0; i < m_board.getRow(); i++)
	{
		stream << char(i + 65) << " #";
		for (int j = 0; j < m_board.getColumn(); j++)
		{
			stream << m_board[i][j] << "#";
		}
		if (i == 4)
			stream << "\t SCORE: " << m_score;
		if (i == 5)
			stream << "\t DISCARDS: " << m_discard;
		stream << endl << "  ###################" << endl;
	}
	stream << endl;
}

/**********************************************************************	
* Purpose: Clears m_board of all altered values
*
* Entry: No values are passed into this function
*
* Exit: No values are returned
*		All Blocks stored within m_board are restored to their default values
*		The Block in the middle of m_board is made a free block
*
************************************************************************/
void GameBoard::clearBoard()
{
	m_block.setFColor(DEFAULT);
	m_block.setSymbol(' ');

	for (int i = 0; i < m_board.getRow(); i++)
	{
		for (int j = 0; j < m_board.getColumn(); j++)
		{
			m_board[i][j] = m_block;
		}
	}

	//initializes the board with the first block in place
	m_board[DEFAULT_BOARD_ROW/2][DEFAULT_BOARD_COLUMN/2].setFColor(GRAY);
	m_board[DEFAULT_BOARD_ROW/2][DEFAULT_BOARD_COLUMN/2].setSymbol('#');
}

/**********************************************************************	
* Purpose: Randomly picks numbers for color and symbol, converts them
*			to valid values by using IntToColors() and IntToSymbols(),
*			respectively, then stores these values in m_block
*
* Entry: Called by getMove()
*		 No values are entered
*
* Exit: Nothing is returned
*
************************************************************************/
void GameBoard::nextBlock()
{
	int color = rand() % (5 + m_level) + 3;
	int symbol = rand() % (5 + m_level);

	//decreases chances of getting a free gray block
	if (color == 3)
		color = rand() % (5 + m_level) + 3;
	//decreases chances of getting a bomb
	if (symbol == 0)
		symbol = rand() % (5 + m_level);

	//if the color is gray, sets the character to a space
	if (color == 3)
	{
		m_block.setFColor(IntToColors(color));
		m_block.setSymbol('#');
	}
	//if the symbol is @, sets the color to default
	else if (symbol == 0)
	{
		color = 11;
		m_block.setFColor(IntToColors(color));
		m_block.setSymbol(IntToSymbols
			
			(symbol));
	}
	else
	{
		m_block.setFColor(IntToColors(color));
		m_block.setSymbol(IntToSymbols(symbol));
	}
}

/**********************************************************************	
* Purpose: Returns m_level which stores what level the game is on
*
* Entry: No values are entered
*
* Exit: m_level is returned
*
************************************************************************/
int GameBoard::getLevel() const
{
	return m_level;
}

/**********************************************************************	
* Purpose: Increments m_level by one
*
* Entry: No values are entered
*
* Exit: No value is returned
*
************************************************************************/
void GameBoard::incLevel()
{
	m_level++;
}

/**********************************************************************	
* Purpose: Returns m_score which stores the running total of points
*
* Entry: No values are entered
*
* Exit: m_score is returned
*
************************************************************************/
int GameBoard::getScore() const
{
	return m_score;
}

/**********************************************************************	
* Purpose: Returns m_discard which stores the number of discards currently
*			being held against the client
*
* Entry: No values are entered
*
* Exit: m_discard is returned
*
************************************************************************/
int GameBoard::getDiscard() const
{
	return m_discard;
}

/**********************************************************************	
* Purpose: Returns m_empty_blocks which stores how many empty blocks 
*			are on the board
*
* Entry: No values are entered
*
* Exit: m_empty_blocks is returned
*
************************************************************************/
int GameBoard::getEmptyBlocks() const
{
	return m_empty_blocks;
}

/**********************************************************************	
* Purpose: Returns stream which is the output stream for the gameboard
*
* Entry: No values are entered
*
* Exit: stream is returned
*
************************************************************************/
ostream& GameBoard::getOutStream() const
{
	return stream;
}

/**********************************************************************	
* Purpose: Checks the input move to see if it is valid
*
* Entry: Called by getMove()
*		 move is the string input by the user, representing the position
*		  of m_board they would like to place m_block
*		 move[1] must be between a and h, move[2] must be between 0 and 9
*		 If move == "DD", then m_block is discarded
*
* Exit: Calls checkMove() to check if the color/symbol position in surrounding
*		 blocks meets requirements
*		valid_move is returned, true if m_block can be placed at the indicated
*		 position, false if not
*		
*
************************************************************************/
bool GameBoard::isMoveValid(const string move)
{
	bool valid_move = false;

	if ((move[0] == 'D' || move[0] == 'd') && (move[1] == 'D' || move[1] == 'd'))
	{
		m_discard++;
		valid_move = true;
	}
	else
	{
		int row = int(move[0]);
		//48 being the ASCII int value for '0'
		int column = int(move[1]) - 48;

		//97 being the ASCII int value for 'a', 104 being the ASCII int value for 'h'
		if (row >= 97 && row <= 104)
		{
			row = row - 97;
		}
		//65 being the ASCII int value for 'A', 72 being the ASCII int value for 'H'
		else if (row >= 65 && row <= 72)
		{
			row = row - 65;
		}
		else
		{
			throw Exception("First character is out of bounds");
		}

		if (column < 0 || column > 8)
		{
			throw Exception("Second character is out of bounds");
		}

		valid_move = checkMove(row, column);
	}

	return valid_move;
}

/**********************************************************************	
* Purpose: Checks m_board to see if the input move is valid
*
* Entry: Called by isMoveValid()
*		 row and column specify the position in m_board that the user
*		  would like to place m_block
*
* Exit: Calls placeBlock() if the move is valid
*		valid_move is returned, true if m_block is placed at the indicated
*		 position, false if not
*		
*
************************************************************************/
bool GameBoard::checkMove(int row, int column)
{
	bool valid_move = true;
	int blank_blocks = 0;

	if ((m_block.getSymbol() == '@') && (m_board[row][column].getSymbol() == ' '))
	{
		throw Exception("@ must be placed on a symbol");
	}
	else if (m_block.getSymbol() != '@' && m_board[row][column].getSymbol() != ' ')
	{
		throw Exception("You cannot place this symbol on top of another symbol");
	}

	if ((m_block.getSymbol() == '@'))
	{
		placeBlock(row, column);
		valid_move = true;
	}
	else
	{
		//checks the block to the right
		if (column + 1 < m_board.getColumn() && valid_move == true)
		{
			if (m_board[row][column + 1].getFColor() == GRAY)
					valid_move = true;
			else if (m_board[row][column + 1].getFColor() == DEFAULT)
			{
				valid_move = true;
				blank_blocks++;
			}
			else if (m_board[row][column + 1].getFColor() == m_block.getFColor() || m_board[row][column + 1].getSymbol() == m_block.getSymbol())
			{
				valid_move = true;
			}
			else if (m_board[row][column + 1].getFColor() != m_block.getFColor() || m_board[row][column + 1].getSymbol() != m_block.getSymbol())
			{
				if (m_board[row][column + 1].getFColor() == GOLD || m_board[row][column + 1].getSymbol() == ' ')
				{
					valid_move = true;
					blank_blocks++;
				}
				else if (m_block.getFColor() == GRAY)
				{
					valid_move = true;
				}
				else
					valid_move = false;
			}
		}
		else
		{
			blank_blocks++;
		}

		//checks the block to the left
		if (column - 1 >= 0 && valid_move == true)
		{
			if (m_board[row][column - 1].getFColor() == GRAY)
					valid_move = true;
			else if (m_board[row][column - 1].getFColor() == DEFAULT)
			{
				valid_move = true;
				blank_blocks++;
			}
			else if (m_board[row][column - 1].getFColor() == m_block.getFColor() || m_board[row][column - 1].getSymbol() == m_block.getSymbol())
			{
				valid_move = true;
			}
			else if (m_board[row][column - 1].getFColor() != m_block.getFColor() || m_board[row][column - 1].getSymbol() != m_block.getSymbol())
			{
				if (m_board[row][column - 1].getFColor() == GOLD || m_board[row][column - 1].getSymbol() == ' ')
				{
					valid_move = true;
					blank_blocks++;
				}
				else if (m_block.getFColor() == GRAY)
				{
					valid_move = true;
				}
				else
					valid_move = false;
			}
		}
		else
		{
			blank_blocks++;
		}

		//checks the block below
		if (row + 1 < m_board.getRow() && valid_move == true)
		{
			if (m_board[row + 1][column].getFColor() == GRAY)
					valid_move = true;
			else if (m_board[row + 1][column].getFColor() == DEFAULT)
			{
				valid_move = true;
				blank_blocks++;
			}
			else if (m_board[row + 1][column].getFColor() == m_block.getFColor() || m_board[row + 1][column].getSymbol() == m_block.getSymbol())
			{
				valid_move = true;
			}
			else if (m_board[row + 1][column].getFColor() != m_block.getFColor() || m_board[row + 1][column].getSymbol() != m_block.getSymbol())
			{
				if (m_board[row + 1][column].getFColor() == GOLD || m_board[row + 1][column].getSymbol() == ' ')
				{
					valid_move = true;
					blank_blocks++;
				}
				else if (m_block.getFColor() == GRAY)
				{
					valid_move = true;
				}
				else
					valid_move = false;
			}
		}
		else
		{
			blank_blocks++;
		}

		//checks the block below
		if (row - 1 >= 0 && valid_move == true)
		{
			if (m_board[row - 1][column].getFColor() == GRAY)
					valid_move = true;
			else if (m_board[row - 1][column].getFColor() == DEFAULT)
			{
				valid_move = true;
				blank_blocks++;
			}
			else if (m_board[row - 1][column].getFColor() == m_block.getFColor() || m_board[row - 1][column].getSymbol() == m_block.getSymbol())
			{
				valid_move = true;
			}
			else if (m_board[row - 1][column].getFColor() != m_block.getFColor() || m_board[row - 1][column].getSymbol() != m_block.getSymbol())
			{
				if (m_board[row - 1][column].getFColor() == GOLD || m_board[row - 1][column].getSymbol() == ' ')
				{
					valid_move = true;
					blank_blocks++;
				}
				else if (m_block.getFColor() == GRAY)
				{
					valid_move = true;
				}
				else
					valid_move = false;
			}
		}
		else
		{
			blank_blocks++;
		}

		if (blank_blocks == 4)
		{
			throw Exception("You must place the symbol next to another symbol matching it's type or color");
		}
		else if (!valid_move)
		{
			throw Exception("You cannot place the symbol in the specified area");
		}

		placeBlock(row, column);
	}

	return valid_move;
}

/**********************************************************************	
* Purpose: Places m_block on m_board
*
* Entry: Called by checkMove()
*		 row and column represent the position on m_board where the block
*		  is to be placed
*
* Exit: The m_block is copied into the block at m_board[row][column]
*		 or the symbol at m_board[row][column] is cleared if the symbol of m_block is '@'
		Calls checkRowColumnClear() to see if either the row, column, or 
*		 both are "full"
*		Increments score by 5
*		Decrements discard by 1, if discard is greater than 0
*		No values are returned		
*
************************************************************************/
void GameBoard::placeBlock(int row, int column)
{
	if (m_board[row][column].getSymbol() == ' ' && m_board[row][column].getFColor() == DEFAULT)
		m_empty_blocks--;

	if (m_block.getSymbol() == '@')
	{
		m_board[row][column].setSymbol(' ');
		m_board[row][column].setFColor(GOLD);
	}
	else
	{
		m_board[row][column] = m_block;
	}

	if (m_discard != 0)
		m_discard--;
	m_score = m_score + 5;

	checkRowColumnClear(row, column);
}

/**********************************************************************	
* Purpose: Checks both the row and column that m_block was placed into
*			to see if they need to be cleared
*
* Entry: Called by placeBlock()
*		 row and column represent the position on m_board where the block
*		  was placed
*
* Exit: If all Blocks within row, or all Blocks within column have symbols
*		 other than ' ', clearRow() and/or clearColumn() are called, respectively
*		No value is returned
*
************************************************************************/
void GameBoard::checkRowColumnClear(int row, int column)
{
	bool is_row_full = true;
	bool is_column_full = true;

	for (int i = 0; i < m_board.getColumn(); i++)
	{
		if (m_board[row][i].getSymbol() == ' ')
		{
			is_row_full = false;
		}
	}
	for (int i = 0; i < m_board.getRow(); i++)
	{
		if (m_board[i][column].getSymbol() == ' ')
		{
			is_column_full = false;
		}
	}

	if (is_column_full)
		clearColumn(column);

	if (is_row_full)
		clearRow(row);
}

/**********************************************************************	
* Purpose: Clears the given row of all symbols, sets the color to GOLD
*			to indicate that the block has been filled
*
* Entry: Called by checkRowColumnClear()
*		 row is the row which needs to be cleared
*
* Exit: All Blocks within specified row have their symbols set to ' '
*			and their color set to GOLD
*
************************************************************************/
void GameBoard::clearRow(int row)
{
	for (int i = 0; i < m_board.getColumn(); i++)
	{
		m_board[row][i].setSymbol(' ');
		m_board[row][i].setFColor(GOLD);
	}
}

/**********************************************************************	
* Purpose: Clears the given column of all symbols, sets the color to GOLD
*			to indicate that the block has been filled
*
* Entry: Called by checkRowColumnClear()
*		 column is the column which needs to be cleared
*
* Exit: All Blocks within specified column have their symbols set to ' '
*			and their color set to GOLD
*
************************************************************************/
void GameBoard::clearColumn(int column)
{
	for (int i = 0; i < m_board.getRow(); i++)
	{
		m_board[i][column].setSymbol(' ');
		m_board[i][column].setFColor(GOLD);
	}
}

/**********************************************************************	
* Purpose: Converts the given int value to an int representing a color
*
* Entry: Called by nextBlock()
*		 color is the int value to be evaluated
*		 color must be greater than 0 and less than 12
*
* Exit: aSymbol is returned
*
************************************************************************/
int GameBoard::IntToColors(int color) 
{
	int r_color;

	switch (color)
	{
		case 0:
			r_color = BLACK;
			break;
		case 1:
			r_color = GOLD;
			break;
		case 2:
			r_color = WHITE;
			break;
		case 3:
			r_color = GRAY;
			break;
		case 4:
			r_color = YELLOW;
			break;
		case 5:
			r_color = RED;
			break;
		case 6:
			r_color = GREEN;
			break;
		case 7:
			r_color = BLUE;
			break;
		case 8:
			r_color = PURPLE;
			break;
		case 9:
			r_color = AQUA;
			break;
		case 10:
			r_color = LPURPLE;
			break;
		case 11:
			r_color = DEFAULT;
			break;
		default:
			r_color = DEFAULT;
	}

	return r_color;
}

/**********************************************************************	
* Purpose: Converts the given int value to a char symbol
*
* Entry: Called by nextBlock()
*		 symbol is the int value to be evaluated
*		 symbol must be greater than 0 and less than 8
*
* Exit: aSymbol is returned
*
************************************************************************/
char GameBoard::IntToSymbols(int symbol)
{
	char aSymbol;

	switch (symbol)
	{
	case 0:
		aSymbol = '@';
		break;
	case 1:
		aSymbol = '*';
		break;
	case 2:
		aSymbol = '~';
		break;
	case 3:
		aSymbol = '^';
		break;
	case 4:
		aSymbol = '%';
		break;
	case 5: 
		aSymbol = '&';
		break;
	case 6:
		aSymbol = '$';
		break;
	case 7:
		aSymbol = '!';
		break;
	default:
		aSymbol = ' ';
	}

	return aSymbol;
}

#endif
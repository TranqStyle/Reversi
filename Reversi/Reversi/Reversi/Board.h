// Reversi Board related class

#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <bitset>

const int boardDimension = 8;

class Board {
public:
	Board(); // constructor
	void initBoard(); // initializes the board
	void draw() const; // draws the current state of the board
	void countPieces(); // counts the current white and black pieces on the board as well as empty spaces
	bool isValid(int, int,unsigned short int); // checks if a move is valid.
	void passTurn(); // used to pass the turn.
	bool getTurn() const; // returns whose turn it is.
	void placePiece(); // places the last played move on the board
	void flipPieces(); // flips the pieces for the set flags.
	void setFlipFlag(); // sets the flipDirection flags.
	void setLastRow(int); // sets the last placed piece's row
	void setLastColumn(int); // sets the last placed piece's column
	int getLastRow() const; // returns the last placed piece's row
	int getLastColumn() const; // returns the last placed piece's column
	int getBlack() const; // returns the black pieces currently on the board
	int getWhite() const; // returns the white pieces currently on the board
	int getEmpty() const; // returns the empty spaces currently on the board

private:
	std::array<std::array<int, boardDimension>, boardDimension> boardArray; // the 8x8 board
	int black{ 0 }; // number of black pieces on the board
	int white{ 0 }; // number of white pieces on the board
	int empty{ 0 }; // number of empty space on the board
	std::bitset<1> turn; // black for '0', white for '1';
	std::bitset<8> flipDirection; // flip Direction for valid moves, 0th element -> top, 1st -> top right, 2nd -> right, 3rd -> bottom right and continues clockwise.
	int lastRow{ 0 }; // last placed piece's row
	int lastColumn{ 0 }; // last placed piece's column


};
#endif

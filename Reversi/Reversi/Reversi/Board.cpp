// Member function definitions of class Board

#include "Board.h"
#include <array>
#include <iostream>

Board::Board() {
	initBoard();
}

void Board::initBoard() { // initializes the board to starting setup
	// initializing an empty board
	for (auto a = boardArray.begin(); a != boardArray.end(); ++a) {
		for (auto b = a->begin(); b != a->end(); ++b) {
			*b = 0;
		}
	}
	// initializing centre black pieces
	boardArray[4][3] = 1;
	boardArray[3][4] = 1;
	
	// initializing centre white pieces
	boardArray[3][3] = 2;
	boardArray[4][4] = 2;

	// initializing the black and white piece counts and empty space count.
	black = 2;
	white = 2;
	empty = 60;

	// resetting every flag
	turn.reset();
	flipDirection.reset();
}

void Board::draw() const{ // draws the current state of the board
	
	// prints the notation letters 'A' to 'H' and character '|' to separate them
	std::cout << "  " << "|";
	char notationLetter = 'A';
	for (int i{ 0 }; i < 8; ++i) {
		std::cout << notationLetter << "|";
		notationLetter += 1;
	}
	std::cout << std::endl;
	
	// draws a line between the board and the notation symbols
	std::cout << " ";
	for (size_t i{ 0 }; i < 18; ++i) {
		std::cout << '-';
	}
	std::cout << std::endl;
	
	// printing both the notation numbers and the board
	int notationNumber{ 1 };
	for (auto arrayIt = boardArray.begin(); arrayIt != boardArray.end(); ++arrayIt) {
		std::cout << " " << notationNumber << "|"; // prints the notation numbers
		for (auto subArrayIt = arrayIt->begin(); subArrayIt != arrayIt->end(); ++subArrayIt) {
			std::cout << *subArrayIt << " "; // prints the row on the board
		}
		std::cout << std::endl;
		++notationNumber;
	}

}

void Board::countPieces() { // counts the pieces and empty spaces on the board
	for (auto itRow = boardArray.begin(); itRow != boardArray.end(); ++itRow) {
		for (auto itCol = itRow->begin(); itCol != itRow->end(); ++itCol) {
			if (*itCol == 0) { // 0 represents empty space
				++empty;
			}
			else if (*itCol == 1) { // 1 represents black pieces
				++black;
			}
			else { // 2 represents white pieces
				++white;
			}
		}
	}

}

// checks if the given move is valid and sets the flags for flipping
bool Board::isValid(int row, int column, unsigned short int tempTurn) {
	if (tempTurn == 0) { // black's turn
		// checking if the current move flips any pieces above it
		if (row > 1 && (boardArray[row - 1][column] == 2)) {
			for (int x{ row - 1 }; x >= 0; --x) {
				if (boardArray[x][column] == 1) { // if we encounter another black piece on that line
					return true;
				}
			}
		}
		// checking if the current move flips any pieces at the top right of it
		if (row > 1 && column < 6 && (boardArray[row - 1][column + 1] == 2)) {
			for (int x{ row - 1 }, y{ column + 1 }; x >= 0 && y <= 7; --x, ++y) {
				if (boardArray[x][y] == 1) { // if we encounter another black piece on that line
					return true;
				}
			}
		}
		// checking if the current move flips any pieces at the right of it
		if (column < 6 && (boardArray[row][column + 1] == 2)) {
			for (int y{ column + 1 }; y <= 7; ++y) {
				if (boardArray[row][y] == 1) { // if we encounter another black piece on that line
					return true;
				}
			}
		}
		// checking if the current move flips any pieces at the bottom right of it
		if (row < 6 && column < 6 && (boardArray[row + 1][column + 1] == 2)) {
			for (int x{row + 1}, y{ column + 1 }; x <= 7 && y <= 7; ++x, ++y) {
				if (boardArray[x][y] == 1) { // if we encounter another black piece on that line
					return true;
				}
			}
		}
		// checking if the current move flips any pieces at the bottom of it
		if (row < 6 && (boardArray[row + 1][column] == 2)) {
			for (int x{ row + 1 }; x <= 7; ++x) {
				if (boardArray[x][column] == 1) { // if we encounter another black piece on that line
					return true;
				}
			}
		}
		// checking if the current move flips any pieces at the bottom left of it
		if (row < 6 && column > 1 && (boardArray[row + 1][column - 1] == 2)) {
			for (int x{ row + 1 }, y{ column - 1 }; x <= 7 && y >= 0; ++x, --y) {
				if (boardArray[x][y] == 1) { // if we encounter another black piece on that line
					return true;
				}
			}
		}
		// checking if the current move flips any pieces at the left of it
		if (column > 1 && (boardArray[row][column - 1] == 2)) {
			for (int y{ column - 1 }; y >= 0; --y) {
				if (boardArray[row][y] == 1) { // if we encounter another black piece on that line
					return true;
				}
			}
		}
		// checking if the current move flips any pieces at the top left of it
		if (row > 1 && column > 1 && (boardArray[row - 1][column - 1] == 2)) {
			for (int x{ row - 1 }, y{ column - 1 }; x >= 0 && y >= 0; --x, --y) {
				if (boardArray[x][y] == 1) { // if we encounter another black piece on that line
					return true;
				}
			}
		}
	}
	else { // white's turn.
		// checking if the current move flips any pieces above it
		if (row > 1 && (boardArray[row - 1][column] == 1)) {
			for (int i{ row - 1 }; i >= 0; --i) {
				if (boardArray[i][column] == 2) { // if we encounter another white piece on that line
					return true;
				}
			}
		}
		// checking if the current move flips any pieces at the top right of it
		if (row > 1 && column < 6 && (boardArray[row - 1][column + 1] == 1)) {
			for (int x{ row - 1 }, y{ column + 1 }; x >= 0 && y <= 7; --x, ++y) {
				if (boardArray[x][y] == 2) { // if we encounter another white piece on that line
					return true;
				}
			}
		}
		// checking if the current move flips any pieces at the right of it
		if (column < 6 && (boardArray[row][column + 1] == 1)) {
			for (int y{ column + 1 }; y <= 7; ++y) {
				if (boardArray[row][y] == 2) { // if we encounter another white piece on that line
					return true;
				}
			}
		}
		// checking if the current move flips any pieces at the bottom right of it
		if (row < 6 && column < 6 && (boardArray[row + 1][column + 1] == 1)) {
			for (int x{ row + 1 }, y{ column + 1 }; x <= 7 && y <= 7; ++x, ++y) {
				if (boardArray[x][y] == 2) { // if we encounter another white piece on that line
					return true;
				}
			}
		}
		// checking if the current move flips any pieces at the bottom of it
		if (row < 6 && (boardArray[row + 1][column] == 1)) {
			for (int x{ row + 1 }; x <= 7; ++x) {
				if (boardArray[x][column] == 2) { // if we encounter another white piece on that line
					return true;
				}
			}
		}
		// checking if the current move flips any pieces at the bottom left of it
		if (row < 6 && column > 1 && (boardArray[row + 1][column - 1] == 1)) {
			for (int x{ row + 1 }, y{ column - 1 }; x <= 7 && y >= 0; ++x, --y) {
				if (boardArray[x][y] == 2) { // if we encounter another white piece on that line
					return true;
				}
			}
		}
		// checking if the current move flips any pieces at the left of it
		if (column > 1 && (boardArray[row][column - 1] == 1)) {
			for (int y{ column - 1 }; y >= 0; --y) {
				if (boardArray[row][y] == 2) { // if we encounter another black piece on that line
					return true;
				}
			}
		}
		// checking if the current move flips any pieces at the top left of it
		if (row > 1 && column > 1 && (boardArray[row - 1][column - 1] == 1)) {
			for (int x{ row - 1 }, y{ column - 1 }; x >= 0 && y >= 0; --x, --y) {
				if (boardArray[x][y] == 2) { // if we encounter another black piece on that line
					return true;
				}
			}
		}
	}
	return false;
}

void Board::flipPieces() {
	if (!getTurn()) { // black's turn
		if (flipDirection[0]) { // flips opposite pieces at top side of the last placed piece
			for (int x{ getLastRow() - 1}; x >= 0; --x) {
				if (boardArray[x][getLastColumn()] == 2) {
					boardArray[x][getLastColumn()] = 1;
				}
			}
		}
		if (flipDirection[1]) { // flips opposite pieces at top right side of the last placed piece
			for (int x{ getLastRow() - 1 }, y{getLastColumn() + 1}; x >= 0 && y <= 7; --x, ++y) {
				if (boardArray[x][y] == 2) {
					boardArray[x][y] = 1;
				}
			}
		}
		if (flipDirection[2]) { // flips opposite pieces at right side of the last placed piece
			for (int y{ getLastColumn() + 1 }; y <= 7; ++y) {
				if (boardArray[getLastRow()][y] == 2) {
					boardArray[getLastRow()][y] = 1;
				}
			}
		}
		if (flipDirection[3]) { // flips opposite pieces at bottom right of the last placed piece
			for (int x{ getLastRow() + 1 }, y{ getLastColumn() + 1 }; x <= 7 && y <= 7; ++x, ++y) {
				if (boardArray[x][y] == 2) {
					boardArray[x][y] = 1;
				}
			}
		}
		if (flipDirection[4]) { // flips opposite pieces at bottom side of the last placed piece
			for (int x{ getLastRow() + 1 }; x <= 7; ++x) {
				if (boardArray[x][getLastColumn()] == 2) {
					boardArray[x][getLastColumn()] = 1;
				}
			}
		}
		if (flipDirection[5]) { // flips opposite pieces at bottom left of the last placed piece
			for (int x{ getLastRow() + 1 }, y{ getLastColumn() - 1 }; x <= 7 && y >= 0; ++x, --y) {
				if (boardArray[x][y] == 2) {
					boardArray[x][y] = 1;
				}
			}
		}
		if (flipDirection[6]) { // flips opposite pieces at left of the last placed piece
			for (int y{ getLastColumn() - 1 };y >= 0; --y) {
				if (boardArray[getLastRow()][y] == 2) {
					boardArray[getLastRow()][y] = 1;
				}
			}
		}
		if (flipDirection[7]) { // flips opposite pieces at top left of the last placed piece
			for (int x{ getLastRow() - 1 }, y{ getLastColumn() - 1 }; x >= 0 && y >= 0; --x, --y) {
				if (boardArray[x][y] == 2) {
					boardArray[x][y] = 1;
				}
			}
		}
	}
	else { // white's turn
		if (flipDirection[0]) { // flips opposite pieces at top side of the last placed piece
			for (int x{ getLastRow() - 1 }; x >= 0; --x) {
				if (boardArray[x][getLastColumn()] == 1) {
					boardArray[x][getLastColumn()] = 2;
				}
			}
		}
		if (flipDirection[1]) { // flips opposite pieces at top right side of the last placed piece
			for (int x{ getLastRow() - 1 }, y{ getLastColumn() + 1 }; x >= 0 && y <= 7; --x, ++y) {
				if (boardArray[x][y] == 1) {
					boardArray[x][y] = 2;
				}
			}
		}
		if (flipDirection[2]) { // flips opposite pieces at right side of the last placed piece
			for (int y{ getLastColumn() + 1 }; y <= 7; ++y) {
				if (boardArray[getLastRow()][y] == 1) {
					boardArray[getLastRow()][y] = 2;
				}
			}
		}
		if (flipDirection[3]) { // flips opposite pieces at bottom right of the last placed piece
			for (int x{ getLastRow() + 1 }, y{ getLastColumn() + 1 }; x <= 7 && y <= 7; ++x, ++y) {
				if (boardArray[x][y] == 1) {
					boardArray[x][y] = 2;
				}
			}
		}
		if (flipDirection[4]) { // flips opposite pieces at bottom side of the last placed piece
			for (int x{ getLastRow() + 1 }; x <= 7; ++x) {
				if (boardArray[x][getLastColumn()] == 1) {
					boardArray[x][getLastColumn()] = 2;
				}
			}
		}
		if (flipDirection[5]) { // flips opposite pieces at bottom left of the last placed piece
			for (int x{ getLastRow() + 1 }, y{ getLastColumn() - 1 }; x <= 7 && y >= 0; ++x, --y) {
				if (boardArray[x][y] == 1) {
					boardArray[x][y] = 2;
				}
			}
		}
		if (flipDirection[6]) { // flips opposite pieces at left of the last placed piece
			for (int y{ getLastColumn() - 1 }; y >= 0; --y) {
				if (boardArray[getLastRow()][y] == 1) {
					boardArray[getLastRow()][y] = 2;
				}
			}
		}
		if (flipDirection[7]) { // flips opposite pieces at top left of the last placed piece
			for (int x{ getLastRow() - 1 }, y{ getLastColumn() - 1 }; x >= 0 && y >= 0; --x, --y) {
				if (boardArray[x][y] == 1) {
					boardArray[x][y] = 2;
				}
			}
		}
	}
	flipDirection.reset();
}

void Board::setFlipFlag() {
	flipDirection.reset();
	if (getTurn() == 0) { // black's turn
		// checking if the current move flips any pieces above it
		if (getLastRow() > 1 && (boardArray[getLastRow() - 1][getLastColumn()] == 2)) {
			for (int x{ getLastRow() - 1}; x >= 0; --x) {
				if (boardArray[x][getLastColumn()] == 1) { // if we encounter another black piece on that line
					flipDirection.flip(0);
				}
			}
		}
		// checking if the current move flips any pieces at the top right of it
		if (getLastRow() > 1 && getLastColumn() < 6 && (boardArray[getLastRow() - 1][getLastColumn() + 1] == 2)) {
			for (int x{ getLastRow() - 1}, y{getLastColumn() + 1}; x >= 0 && y <= 7; --x, ++y) {
				if (boardArray[x][y] == 1) { // if we encounter another black piece on that line
					flipDirection.flip(1);
				}
			}
		}
		// checking if the current move flips any pieces at the right of it
		if (getLastColumn() < 6 && (boardArray[getLastRow()][getLastColumn() + 1] == 2)) {
			for (int y{ getLastColumn() + 1}; y <= 7; ++y) {
				if (boardArray[getLastRow()][y] == 1) { // if we encounter another black piece on that line
					flipDirection.flip(2);
				}
			}
		}
		// checking if the current move flips any pieces at the bottom right of it
		if (getLastRow() < 6 && getLastColumn() < 6 && (boardArray[getLastRow() + 1][getLastColumn() + 1] == 2)) {
			for (int x{ getLastRow() + 1}, y{getLastColumn() + 1}; x <= 7 && y <= 7; ++x, ++y) {
				if (boardArray[x][y] == 1) { // if we encounter another black piece on that line
					flipDirection.flip(3);
				}
			}
		}
		// checking if the current move flips any pieces at the bottom of it
		if (getLastRow() < 6 && (boardArray[getLastRow() + 1][getLastColumn()] == 2)) {
			for (int x{ getLastRow() + 1 }; x <= 7; ++x) {
				if (boardArray[x][getLastColumn()] == 1) { // if we encounter another black piece on that line
					flipDirection.flip(4);
				}
			}
		}
		// checking if the current move flips any pieces at the bottom left of it
		if (getLastRow() < 6 && getLastColumn() > 1 && (boardArray[getLastRow() + 1][getLastColumn() - 1] == 2)) {
			for (int x{ getLastRow() + 1 }, y{ getLastColumn() - 1 }; x <= 7 && y >= 0; ++x, --y) {
				if (boardArray[x][y] == 1) { // if we encounter another black piece on that line
					flipDirection.flip(5);
				}
			}
		}
		// checking if the current move flips any pieces at the left of it
		if (getLastColumn() > 1 && (boardArray[getLastRow()][getLastColumn() - 1] == 2)) {
			for (int y{ getLastColumn() - 1 }; y >= 0; --y) {
				if (boardArray[getLastRow()][y] == 1) { // if we encounter another black piece on that line
					flipDirection.flip(6);
				}
			}
		}
		// checking if the current move flips any pieces at the top left of it
		if (getLastRow() > 1 && getLastColumn() > 1 && (boardArray[getLastRow() - 1][getLastColumn() - 1] == 2)) {
			for (int x{ getLastRow() - 1 }, y{ getLastColumn() - 1 }; x >= 0 && y >= 0; --x, --y) {
				if (boardArray[x][y] == 1) { // if we encounter another black piece on that line
					flipDirection.flip(7);
				}
			}
		}
	}
	else { // white's turn.
		// checking if the current move flips any pieces above it
		if (getLastRow() > 1 && (boardArray[getLastRow() - 1][getLastColumn()] == 1)) {
			for (int i{ getLastRow() - 1 }; i >= 0; --i) {
				if (boardArray[i][getLastColumn()] == 2) { // if we encounter another white piece on that line
					flipDirection.flip(0);
				}
			}
		}
		// checking if the current move flips any pieces at the top right of it
		if (getLastRow() > 1 && getLastColumn() < 6 && (boardArray[getLastRow() - 1][getLastColumn() + 1] == 1)) {
			for (int x{ getLastRow() - 1 }, y{ getLastColumn() + 1 }; x >= 0 && y <= 7; --x, ++y) {
				if (boardArray[x][y] == 2) { // if we encounter another white piece on that line
					flipDirection.flip(1);
				}
			}
		}
		// checking if the current move flips any pieces at the right of it
		if (getLastColumn() < 6 && (boardArray[getLastRow()][getLastColumn() + 1] == 1)) {
			for (int y{ getLastColumn() + 1 }; y <= 7; ++y) {
				if (boardArray[getLastRow()][y] == 2) { // if we encounter another white piece on that line
					flipDirection.flip(2);
				}
			}
		}
		// checking if the current move flips any pieces at the bottom right of it
		if (getLastRow() < 6 && getLastColumn() < 6 && (boardArray[getLastRow() + 1][getLastColumn() + 1] == 1)) {
			for (int x{ getLastRow() + 1 }, y{ getLastColumn() + 1 }; x <= 7 && y <= 7; ++x, ++y) {
				if (boardArray[x][y] == 2) { // if we encounter another white piece on that line
					flipDirection.flip(3);
				}
			}
		}
		// checking if the current move flips any pieces at the bottom of it
		if (getLastRow() < 6 && (boardArray[getLastRow() + 1][getLastColumn()] == 1)) {
			for (int x{ getLastRow() + 1 }; x <= 7; ++x) {
				if (boardArray[x][getLastColumn()] == 2) { // if we encounter another white piece on that line
					flipDirection.flip(4);
				}
			}
		}
		// checking if the current move flips any pieces at the bottom left of it
		if (getLastRow() < 6 && getLastColumn() > 1 && (boardArray[getLastRow() + 1][getLastColumn() - 1] == 1)) {
			for (int x{ getLastRow() + 1 }, y{ getLastColumn() - 1 }; x <= 7 && y >= 0; ++x, --y) {
				if (boardArray[x][y] == 2) { // if we encounter another white piece on that line
					flipDirection.flip(5);
				}
			}
		}
		// checking if the current move flips any pieces at the left of it
		if (getLastColumn() > 1 && (boardArray[getLastRow()][getLastColumn() - 1] == 1)) {
			for (int y{ getLastColumn() - 1 }; y >= 0; --y) {
				if (boardArray[getLastRow()][y] == 2) { // if we encounter another black piece on that line
					flipDirection.flip(6);
				}
			}
		}
		// checking if the current move flips any pieces at the top left of it
		if (getLastRow() > 1 && getLastColumn() > 1 && (boardArray[getLastRow() - 1][getLastColumn() - 1] == 1)) {
			for (int x{ getLastRow() - 1 }, y{ getLastColumn() - 1 }; x >= 0 && y >= 0; --x, --y) {
				if (boardArray[x][y] == 2) { // if we encounter another black piece on that line
					flipDirection.flip(7);
				}
			}
		}
	}
}



// places the last played move on the board
void Board::placePiece() {
	if (!getTurn()) { // if black's turn
		boardArray[getLastRow()][getLastColumn()] = 1;
	}
	else { // if white's  turn
		boardArray[getLastRow()][getLastColumn()] = 2;
	}
}

// passes the turn to the other player
void Board::passTurn() {
	turn.flip(0);
}

// gets the current turn. 0 for black, 1 for white
bool Board::getTurn() const{
	return turn[0];
}

void Board::setLastColumn(int column) {
	lastColumn = column;
}

void Board::setLastRow(int row) {
	lastRow = row;
}

int Board::getLastColumn() const {
	return lastColumn;
}

int Board::getLastRow() const {
	return lastRow;
}

int Board::getEmpty() const {
	return empty;
}

int Board::getBlack() const {
	return black;
}

int Board::getWhite() const {
	return white;
}
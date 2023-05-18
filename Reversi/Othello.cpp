 // Member functions definitions for class Othello

#include "Othello.h"
#include "Board.h"
#include <iostream>
#include <string>
#include <cctype>

void Othello::start() { // starts the game and exits when the user wants to exit.
	while (gameStatus != Status::END) {
		Board othelloBoard; // initialize a board object
		while (!checkEnd(othelloBoard)) { // this function will announce whose turn it is will check if the game ends
			othelloBoard.draw();
			promptTurn(othelloBoard);
			getMove(othelloBoard); // gets the move until a correct one is made, commits them.
			othelloBoard.placePiece();
			othelloBoard.setFlipFlag();
			othelloBoard.flipPieces();
			othelloBoard.passTurn();
		}
		announceWinner(othelloBoard);
		othelloBoard.draw();
		askPlay();
	}
}

void Othello::announceWinner(Board othelloBoard) {
	othelloBoard.countPieces();
	if (othelloBoard.getWhite() > othelloBoard.getBlack()) {
		std::cout << "\nWhite: " << othelloBoard.getWhite() + othelloBoard.getEmpty() << " Black: " << othelloBoard.getBlack() << std::endl;
		std::cout << "The winner is: White. Congratulations!" << std::endl;
	}
	else if (othelloBoard.getBlack() > othelloBoard.getWhite()) {
		std::cout << "\nWhite: " << othelloBoard.getWhite() << " Black: " << othelloBoard.getBlack() + othelloBoard.getEmpty() << std::endl;
		std::cout << "The winner is: Black. Congratulations!" << std::endl;
	}
	else if (othelloBoard.getBlack() == othelloBoard.getWhite()) {
		std::cout << "\nWhite: " << othelloBoard.getWhite() << " Black: " << othelloBoard.getBlack() << std::endl;
		std::cout << "The game is a tie." << std::endl;
	}
}

void Othello::askPlay() {
	std::cout << "\nThe game is over, do you want to play another?(1 to play, 2 to exit): ";
	std::string outcome;
	std::cin >> outcome;
	outcome.erase(std::remove_if(outcome.begin(), outcome.end(), ::isspace), outcome.end());
	bool isValidEntry{ false };
	while (!isValidEntry) {
		if (outcome.size() == 1) {
			isValidEntry = true;
		}
		if (outcome[0] == '1' || outcome[0] == '2') {
			isValidEntry = true;
		}
		if (!isValidEntry) {
			std::cout << "\nPlease enter a valid response(1 to play, 2 to exit): ";
			std::cin >> outcome;
			outcome.erase(std::remove_if(outcome.begin(), outcome.end(), ::isspace), outcome.end());
		}
	}
	gameStatus = static_cast<Status>(std::stoi(outcome));
}

bool Othello::checkEnd(Board oBoard) { // checks if there are no moves left by both party
	for (unsigned short int tempTurn{ 0 }; tempTurn < 2; ++tempTurn) {
		for (size_t i{ 0 }; i < 8; ++i) {
			for (size_t j{ 0 }; j < 8; ++j) {
				if (oBoard.isValid(i, j, tempTurn)) {
					return false;
				}
			}
		}
	}
	return true;
}

void Othello::promptTurn(Board oBoard) {
	if (oBoard.getTurn() == 0) {
		std::cout << "\nIt is black's turn.(Represented by 1)" << std::endl;
	}
	else {
		std::cout << "\nIt is white's turn.(Represented by 2)" << std::endl;
	}
}
	


void Othello::getMove(Board& oBoard) {
	std::string moveString;
	bool goodFormat{ false };
	bool goodMove{ false };
	int row{ 0 };
	int column{ 0 };
	std::cout << "\nPlease make a valid move(Format: A5 or a5): ";
	std::cin >> moveString;
	std::string moveStringRemovedWS = removeWS(moveString);
	while (!goodFormat || !goodMove) {
		if (isValidFormat(moveStringRemovedWS)) { // if it's in valid format
			convertNotationToArrayPos(moveStringRemovedWS, row, column); // converts the notation to array indices
			goodFormat = true;
			if (oBoard.isValid(row, column, oBoard.getTurn())) { // if it's a valid move
				goodMove = true;
				commitMove(row, column, oBoard);
			}
			else { // if it's not a valid move
				goodMove = false;
				std::cout << "\nThat's an invalid move. Please enter a valid move(Format: A5 or a5): ";
				std::cin >> moveString;
				moveStringRemovedWS = removeWS(moveString);
			}
		}
		else { // if it's not a valid format
			goodFormat = false;
			std::cout << "\nThat's an invalid move. Please enter a valid move(Format: A5 or a5): ";
			std::cin >> moveString;
			moveStringRemovedWS = removeWS(moveString);
		}
	}
}

void Othello::commitMove(int row, int column, Board &oBoard) {
	oBoard.setLastRow(row);
	oBoard.setLastColumn(column);
}

void Othello::convertNotationToArrayPos(std::string s, int& row, int& column) { // converts the entered move in notation to array positions.
	// converts the first element to column if it's uppercase letter. Example: 'A' to 0
	for (int i{ 65 }; i <= 72; ++i) {
		if (static_cast<int>(s[0]) == i) {
			column = static_cast<int>(s[0]) - 65;
			break;
		}
	}
	
	// converts the first element to column if it's lowercase letter. Example: 'a' to 0
	for (int i{ 97 }; i <= 104; ++i) {
		if (static_cast<int>(s[0]) == i) {
			column = static_cast<int>(s[0]) - 97;
			break;
		}
	}
	// converts the second element to row if it's between 1-8. Example: '8' = 7
	for (int i{ 49 }; i <= 56; ++i) {
		if (static_cast<int>(s[1]) == i) {
			row = static_cast<int>(s[1]) - 49;
			break;
		}
	}
}

bool Othello::isValidFormat(std::string s) { // checks if the format is in the form "A5" or "a5"

	bool firstCharacterValid{ false };
	bool secondCharacterValid{ false };
	// checks if string is 2 characters long according to format it should be
	if (s.size() != 2) {
		return false;
	}

	// checks if the first character is between characters 'A' and 'H'
	for (int i{ 65 }; i <= 72; ++i) {
		if (s[0] == static_cast<char>(i)) {
			firstCharacterValid = true;
			break;
		}
	}
	// checks if the first character is between characters 'a' and 'h'
	for (int i{ 97 }; i <= 104; ++i) {
		if (s[0] == static_cast<char>(i)) {
			firstCharacterValid = true;
			break;
		}
	}
	// checks if the second character is between 1 and 8
	for (int i{ 49 }; i <= 56; ++i) {
		if (s[1] == static_cast<char>(i)) {
			secondCharacterValid = true;
			break;
		}
	}
	// if first character is not valid or second character is not valid
	if (!firstCharacterValid || !secondCharacterValid) {
		return false;
	}

	return true;
}

std::string Othello::removeWS(std::string s) {
	s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
	return s;
}
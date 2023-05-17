// Header for class Othello

#ifndef OTHELLO_H
#define OTHELLO_H

#include "Board.h"
#include <iostream>
#include <string>

class Othello {
public:
	void start(); // starts the game of othello and continues until the user wanna quit.
	bool checkEnd(Board); // checks if game is at an end
	void getMove(Board); // Asks the user for a move, validates it and then saves it.
	void promptTurn(Board); // Prompts whose turn it is.
	std::string removeWS(std::string);
	void askPlay(); // asks player if it wants to continue or not.
	void announceWinner(Board); // announces the winner.


private:
	enum class Status{START, CONTINUE, END};
	Status gameStatus{ Status::START };
	void convertNotationToArrayPos(std::string, int&, int&); // converts the entered move into array elements.
	bool isValidFormat(std::string); // checks if the entered move is in the valid format
	void commitMove(int, int, Board); // sets the last move on the specified board
};

#endif


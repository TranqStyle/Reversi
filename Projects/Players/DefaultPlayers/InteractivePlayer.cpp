#include "InteractivePlayer.h"

#include <iostream>
#include <cctype>
#include <algorithm>

namespace
{
    std::string convertToLower(std::string s)
    {
        std::transform(s.begin(), s.end(), s.begin(),
            [](unsigned char c) { return std::tolower(c); }
        );
        return s;
    }

    Move createMoveFromString(const std::string& s)
    {
        if (s == "pass" || s == "p")
        {
            return Move{};
        }
        else
        {
            int col = s[0] - 'a';       // 'a' -> 0, 'b' -> 1, ..., 'g' -> 6, 'h' -> 7
            int row = 7 - (s[1] - '1'); // '1' -> 7, '2' -> 6, ..., '7' -> 1, '8' -> 0
            return Move(Position{ row, col });
        }
    }

    std::string createStringFromMove(const Move& m)
    {
        if (m.isPass())
        {
            return "pass";
        }
        else
        {
            Position pos = m.getPosition();
            char col = pos.getCol() + 'a';
            char row = (7 - pos.getRow()) + '1';

            std::string result = { col, row };
            return result;
        }
    }
}

InteractivePlayer::InteractivePlayer() : AbstractPlayer("InteractivePlayer")
{
}

Move InteractivePlayer::getMove(const State::CPtr& state)
{
    std::cout << "Valid moves: " << std::endl;
    
    std::set<Move> validMoves = state->getValidMoves();
    for (const auto& move : validMoves)
    {
        std::cout << createStringFromMove(move) << std::endl;
    }
    std::cout << std::endl;
    
    bool firstTry = true;
    Move move;
    do
    {
        if (firstTry)
        {
            firstTry = false;
        }
        else
        {
            std::cout << "Please make a valid move!" << std::endl;
            std::cin.clear();
            std::cin.ignore(10000,'\n');
        }
        std::cout << "Choose a move:" << std::endl;

        move = Move{};

        std::string moveString;
        std::cin >> moveString;
        moveString = convertToLower(moveString);

        try
        {
            move = createMoveFromString(moveString);
        }
        catch (const std::exception&)
        {
            move = Move{};
        }
    } while(!(validMoves.count(move) == 1));
    
    return move;
}

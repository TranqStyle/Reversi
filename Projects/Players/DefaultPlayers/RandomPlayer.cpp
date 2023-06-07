#include "RandomPlayer.h"

#include <iostream>

#include <Utility.h>

RandomPlayer::RandomPlayer() : AbstractPlayer("RandomPlayer")
{
}

Move RandomPlayer::getMove(const State::CPtr& state)
{
    Utility utility;
    
    _logger.log("Valid moves:");
    
    std::set<Move> validMoves = state->getValidMoves();
    for (const auto& move : validMoves)
    {
        _logger.log(move);
    }
    
    Move randomMove = utility.selectRandomElement(validMoves);
    _logger.log("");
    _logger.log("I picked:");
    _logger.log(randomMove);
    
    return randomMove;
}
#include "GameHandler.h"

#include <State.h>

#include <iostream>

GameHandler::GameHandler() : _logger("GameHandler"), _state(std::make_shared<State>())
{
}

void GameHandler::init(const AbstractPlayer::Ptr& player0, const AbstractPlayer::Ptr& player1)
{
    _players.clear();
    _players.push_back(player0);
    _players.push_back(player1);

    _state->restart();
}

State::Outcome GameHandler::play()
{
    Logger::setSilent(_silentLogger);
    _logger.logUnitHead("play()");
    
    _state->restart();
    _moveHistory.clear();
    // TODO: notifyNewGame();
    
    State::Outcome outcome;
    
    try {
        while((outcome = _state->getOutcome()) == State::Outcome::PENDING)
        {
            _logger.log("Player[0] is ", _players[0]->getPreferedName());
            _logger.log("Player[1] is ", _players[1]->getPreferedName());
            
            if (!_moveHistory.empty())
            {
                _logger.log("Last move is ", _moveHistory.back());
            }
                
            _logger.log(*_state); 
            
            State::Player onMove = _state->getOnMove();
            
            Move move = _players[onMove]->getMove(_state);
            
            _state->applyMove(move);
            _moveHistory.push_back(move);
        }
    }
    catch (const std::exception& e)
    {
        State::Player onMove = _state->getOnMove();
        
        _players[onMove]->notifyBadMove(e.what());
        _logger.log("==> ", _players[onMove]->getPreferedName(), " made a fatal mistake:");
        _logger.log(e.what());
        
        outcome = (onMove == State::Player::P0 ? State::Outcome::P1WIN : State::Outcome::P0WIN);
    }
    
    announceWinner(outcome);
    dumpGameInfo();
    _logger.logUnitTail("play()");
    Logger::setSilent(false);
    return outcome;
}

void GameHandler::announceWinner(State::Outcome outcome) const
{
    _logger.log("");
    _logger.log("[End of game snapshot:]");
    _logger.log(*_state);
    Logger::setSilent(false);
    
    switch (outcome)
    {
        case State::Outcome::P0WIN:
            _players[0]->notifyEndGame(_state, AbstractPlayer::VICTORY);
            _players[1]->notifyEndGame(_state, AbstractPlayer::DEFEAT);
            _logger.log("--- Player[0]: ", _players[0]->getPreferedName(), " has won the game ---");
            break;
        
        case State::Outcome::P1WIN:
            _players[0]->notifyEndGame(_state, AbstractPlayer::DEFEAT);
            _players[1]->notifyEndGame(_state, AbstractPlayer::VICTORY);
            _logger.log("--- Player[1]: ", _players[1]->getPreferedName(), " has won the game ---");
            break;
        
        case State::Outcome::DRAW:
            _players[0]->notifyEndGame(_state, AbstractPlayer::DRAW);
            _players[1]->notifyEndGame(_state, AbstractPlayer::DRAW);
            _logger.log("--- The game ended in a draw ---");
            break;
            
        default:
            _logger.log("--- The game ended - outcome could not be determined ---");
            break;
    }
    
    Logger::setSilent(_silentLogger); // if it were true before
}

void GameHandler::dumpGameInfo() const
{
    //std::ofstream ofs("movelist.txt");
}

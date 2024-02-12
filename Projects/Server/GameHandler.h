#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include <AbstractPlayer.h>

#include <Logger.h>

#include <vector>

class GameHandler
{
public:
    GameHandler();
    
    void init(const AbstractPlayer::Ptr& player0, const AbstractPlayer::Ptr& player1);
    State::Outcome play();

private:
    using MoveHistory = std::vector<Move>;

    Logger _logger;
    const bool _silentLogger = false;
    
    State::Ptr _state;
    MoveHistory _moveHistory;
    
    std::vector<AbstractPlayer::Ptr> _players;
    
    void announceWinner(State::Outcome outcome) const;
    void dumpGameInfo() const;
};

#endif // GAMEHANDLER_H


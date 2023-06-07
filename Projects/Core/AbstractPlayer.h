#ifndef ABSTRACTPLAYER_H
#define ABSTRACTPLAYER_H

#include "Logger.h"

#include "Move.h"
#include "State.h"

#include <memory>
#include <string>

class AbstractPlayer
{
public:
    enum PersonalOutcome { DEFEAT, DRAW, VICTORY };

    typedef std::shared_ptr<AbstractPlayer> Ptr;
    virtual ~AbstractPlayer();
    
    virtual Move getMove(const State::CPtr& state) = 0;
    
    // Optional callbacks to implement - default behaviour does nothing for notifyXX()
    virtual void notifyBadMove(const std::string& errorMessage) const;
    virtual void notifyEndGame(const State::CPtr& state, PersonalOutcome personalOutcome) const;
    
    std::string getPreferedName() const;
    
protected:
    const std::string _preferedName;
    Logger _logger;
    
    AbstractPlayer(const std::string& preferedName_ = "Player"); // This is an interface for player, so it cannot be instantiated
};

#endif // ABSTRACTPLAYER_H


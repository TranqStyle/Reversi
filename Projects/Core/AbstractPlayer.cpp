#include "AbstractPlayer.h"

AbstractPlayer::AbstractPlayer(const std::string& preferedName_) : _preferedName(preferedName_), _logger(_preferedName)
{
}

AbstractPlayer::~AbstractPlayer()
{
}

void AbstractPlayer::notifyBadMove(const std::string& errorMessage) const
{
}

void AbstractPlayer::notifyEndGame(const State::CPtr& state, PersonalOutcome personalOutcome) const
{
}

std::string AbstractPlayer::getPreferedName() const
{
    return _preferedName;
}

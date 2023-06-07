#include "StackPlayer.h"

using namespace StackAI;

namespace
{
    std::string personalOutcome2string(AbstractPlayer::PersonalOutcome po)
    {
        switch (po)
        {
            case AbstractPlayer::DEFEAT:  return "Defeat";
            case AbstractPlayer::DRAW:    return "Draw";
            case AbstractPlayer::VICTORY: return "Victory";
            default:                      return "Unrecognized PersonalOutcome";
        }
    }
}

StackPlayer::StackPlayer() : AbstractPlayer("Stack")
{
}

Move StackPlayer::getMove(const State::CPtr& state)
{
    return *(state->getValidMoves().begin());
}

void StackPlayer::notifyEndGame(const State::CPtr& state, PersonalOutcome personalOutcome) const
{
    _logger.log( "The game ending from my perspective: " + personalOutcome2string(personalOutcome) );
}
#include "TranqPlayer.h"

using namespace TranqAI;

TranqPlayer::TranqPlayer() : AbstractPlayer("TranqPlayer")
{
}

Move TranqPlayer::getMove(const State::CPtr& state)
{
    return *(state->getValidMoves().begin());
}

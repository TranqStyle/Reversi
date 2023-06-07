#ifndef TRANQAI_TRANQPLAYER_H
#define TRANQAI_TRANQPLAYER_H

#include <AbstractPlayer.h>

namespace TranqAI
{

class TranqPlayer : public AbstractPlayer
{
public:
    TranqPlayer();
    
    Move getMove(const State::CPtr& state) override;
};

} // TranqAI

#endif // TRANQAI_TRANQPLAYER_H

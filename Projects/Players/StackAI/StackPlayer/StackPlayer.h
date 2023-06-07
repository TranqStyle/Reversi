#ifndef STACKAI_STACKPLAYER_H
#define STACKAI_STACKPLAYER_H

#include <AbstractPlayer.h>

namespace StackAI
{

class StackPlayer : public AbstractPlayer
{
public:
    StackPlayer();
    
    Move getMove(const State::CPtr& state) override;
    
    void notifyEndGame(const State::CPtr& state, PersonalOutcome personalOutcome) const override;

private:
    //
};

} // StackAI

#endif // STACKAI_STACKPLAYER_H

#ifndef DEFAULTPLAYERS_INTERACTIVEPLAYER_H
#define DEFAULTPLAYERS_INTERACTIVEPLAYER_H

#include <AbstractPlayer.h>

class InteractivePlayer : public AbstractPlayer
{
public:
    InteractivePlayer();
    
    Move getMove(const State::CPtr& state) override;
};

#endif // DEFAULTPLAYERS_INTERACTIVEPLAYER_H

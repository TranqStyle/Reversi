#ifndef RANDOMPLAYER_H
#define RANDOMPLAYER_H

#include <AbstractPlayer.h>

class RandomPlayer : public AbstractPlayer
{
public:
    RandomPlayer();
    
    Move getMove(const State::CPtr& state) override;
};

#endif // RANDOMPLAYER_H

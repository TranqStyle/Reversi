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

protected:
    StackPlayer(const std::string& preferedName_);

    virtual size_t getMaxDepth(const State::CPtr& baseState) const;
    virtual double getValueOfState(const State::CPtr& state, size_t remainingDepth, double alpha, double beta, const std::string& tracer) const;
    virtual double getHeuristicValueOfState(const State::CPtr& state) const;
};

} // StackAI

#endif // STACKAI_STACKPLAYER_H

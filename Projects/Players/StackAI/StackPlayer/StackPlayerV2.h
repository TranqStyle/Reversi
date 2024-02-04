#ifndef STACKAI_STACKPLAYERV2_H
#define STACKAI_STACKPLAYERV2_H

#include "StackPlayer.h"

namespace StackAI
{

class StackPlayerV2 : public StackPlayer
{
public:
    StackPlayerV2();

private:
    double getHeuristicValueOfState(const State::CPtr& state) const override;
};

} // StackAI

#endif // STACKAI_STACKPLAYERV2_H

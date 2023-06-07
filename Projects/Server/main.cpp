#include "GameHandler.h"

#include <InteractivePlayer.h>
#include <RandomPlayer.h>

#include <StackPlayer.h>
#include <TranqPlayer.h>

int main()
{
    GameHandler gameHandler{};

    //AbstractPlayer::Ptr player0 = std::make_shared<StackAI::StackPlayer>();
    //AbstractPlayer::Ptr player1 = std::make_shared<TranqAI::TranqPlayer>();

    //AbstractPlayer::Ptr player0 = std::make_shared<RandomPlayer>();
    AbstractPlayer::Ptr player0 = std::make_shared<InteractivePlayer>();
    AbstractPlayer::Ptr player1 = std::make_shared<RandomPlayer>();

    gameHandler.init(player0, player1);

    //for (size_t repeat = 0; repeat < 10; ++repeat)
        gameHandler.play();

    return 0;
}

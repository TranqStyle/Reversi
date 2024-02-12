#include "GameHandler.h"
#include "MultiGameRunner.h"

#include <InteractivePlayer.h>
#include <RandomPlayer.h>

#include <StackPlayer.h>
#include <StackPlayerV2.h>
#include <TranqPlayer.h>

int main()
{
    GameHandler gameHandler{};

    //AbstractPlayer::Ptr player0 = std::make_shared<StackAI::StackPlayer>();
    //AbstractPlayer::Ptr player0 = std::make_shared<StackAI::StackPlayer>();
    //AbstractPlayer::Ptr player0 = std::make_shared<RandomPlayer>();
    AbstractPlayer::Ptr player0 = std::make_shared<InteractivePlayer>();
    
    //AbstractPlayer::Ptr player1 = std::make_shared<RandomPlayer>();
    //AbstractPlayer::Ptr player1 = std::make_shared<TranqAI::TranqPlayer>();
    AbstractPlayer::Ptr player1 = std::make_shared<StackAI::StackPlayerV2>();

    MultiGameRunner gameRunner{ player0, player1, 1 };
    
    gameRunner.play();
    
    return 0;
}

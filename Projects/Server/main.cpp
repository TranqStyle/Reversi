#include "GameHandler.h"
#include "MultiGameRunner.h"

#include <InteractivePlayer.h>
#include <RandomPlayer.h>

#include <StackPlayer.h>
#include <TranqPlayer.h>

int main()
{
    //AbstractPlayer::Ptr player0 = std::make_shared<StackAI::StackPlayer>();
    AbstractPlayer::Ptr player1 = std::make_shared<TranqAI::TranqPlayer>();

    //AbstractPlayer::Ptr player0 = std::make_shared<RandomPlayer>();
    AbstractPlayer::Ptr player0 = std::make_shared<InteractivePlayer>();
    //AbstractPlayer::Ptr player1 = std::make_shared<RandomPlayer>();

    MultiGameRunner gameRunner{ player0, player1, 1 };
    
    gameRunner.play();
    
    std::cout << gameRunner;
    
    return 0;
}

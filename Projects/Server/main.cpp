#include "GameHandler.h"
#include "GameCounter.h"

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

    GameCounter gameCounter{ player0, player1, 1 };
    
    gameCounter.play();
    
    std::cout << gameCounter;
    
    return 0;
}

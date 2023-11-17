#include "GameHandler.h"

#include <InteractivePlayer.h>
#include <RandomPlayer.h>

#include <StackPlayer.h>
#include <TranqPlayer.h>

int main()
{
    size_t p0win{ 0 };
    size_t p1win{ 0 };
    size_t draw{ 0 };
    size_t gameSample{ 500 };

    GameHandler gameHandler{};

    //AbstractPlayer::Ptr player0 = std::make_shared<StackAI::StackPlayer>();
    AbstractPlayer::Ptr player1 = std::make_shared<TranqAI::TranqPlayer>();

    //AbstractPlayer::Ptr player0 = std::make_shared<RandomPlayer>();
    AbstractPlayer::Ptr player0 = std::make_shared<InteractivePlayer>();
    //AbstractPlayer::Ptr player1 = std::make_shared<RandomPlayer>();
    for (size_t i{ 0 }; i < gameSample; ++i) {

        gameHandler.init(player0, player1);

        //for (size_t repeat = 0; repeat < 10; ++repeat)
        State::Outcome result = gameHandler.play();
        if (result == State::Outcome::P0WIN) {
            ++p0win;
        }
        else if (result == State::Outcome::P1WIN) {
            ++p1win;
        }
        else if (result == State::Outcome::DRAW) {
            ++draw;
        }
    }
    std::cout << "After a " << gameSample << " games:\nP0 won: " << p0win << "\nP1 won: " << p1win << "\nDraws : " << draw;
    return 0;
}

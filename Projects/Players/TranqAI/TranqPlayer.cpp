#include "TranqPlayer.h"
#include "Utility.h"
#include "MoveWithMetrics.h"
#include "MoveEvaluation.h"
#include <utility>
#include <iterator>
#include <stdexcept>

using namespace TranqAI;


TranqPlayer::TranqPlayer() : AbstractPlayer("TranqPlayer")
{
}

// TODO: add a "mixed" type which compares mobility and most pieces and picks the better move.
Move TranqPlayer::getMove(const State::CPtr& state)
{
    std::set<Move> moveList = state->getValidMoves();
    if (moveList.size() == 1 && *moveList.begin() == Move{}) {
        return Move{};
    } 
    else if (moveList.size() > 0) {
         std::vector<MoveWithMetrics> moves{};
         for (const Move& move : moveList) {
             moves.push_back(MoveWithMetrics{ state,  move , 0.30, 0.70 });
         }
         MoveEvaluation eval(moves);
         std::vector<MoveWithMetrics> bestMixedMoves = eval.calculateNMovesMixed(1);
         return bestMixedMoves[0].getMove();
    }
    else {
        throw std::runtime_error{ "Invalid move set size." };
    }
}

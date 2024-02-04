#include "StackPlayerV2.h"

#include <optional>
#include <algorithm>

using namespace StackAI;

namespace
{
    template <typename T>
    int sgn(T val)
    {
        return (T(0) < val) - (val < T(0));
    }

    int cornerAdjacentIdx(int cornerIdx)
    {
        if (cornerIdx == 0)
            return cornerIdx + 1;
        else
            return cornerIdx - 1;
    }

    int getSgnFromPlayerEquality(State::Player myPlayer, State::Player opponentPlayer, State::Player owner)
    {
        if (myPlayer == owner)
        {
            return +1;
        }
        else if (opponentPlayer == owner)
        {
            return -1;
        }
        return 0;
    }

    double getCornerScore(State::Player myPlayer, State::Player cornerPlayer, std::vector<State::Player> borderPlayers, State::Player diagonalPlayer)
    {
        const double cornerScore   = +0.24; // +
        const double borderScore   = -0.02; // -
        const double diagonalScore = -0.03; // -

        State::Player opponentPlayer = State::oppositePlayer(myPlayer);

        double result = 0.0;

        result += cornerScore * getSgnFromPlayerEquality(myPlayer, opponentPlayer, cornerPlayer);
        if (cornerPlayer != State::Player::NONE)
            return result;  // Corner ownership decides everything

        for (State::Player borderPlayer : borderPlayers)
        {
            result += borderScore * getSgnFromPlayerEquality(myPlayer, opponentPlayer, borderPlayer);
        }
        
        result += diagonalScore * getSgnFromPlayerEquality(myPlayer, opponentPlayer, diagonalPlayer);

        return result;
    }

    double getCornerScore(State::Player myPlayer, const State::Table& table, int cornerRowIdx, int cornerColIdx)
    {
        State::Player cornerPlayer = table[cornerRowIdx][cornerColIdx];

        State::Player borderPlayer0 = table[cornerAdjacentIdx(cornerRowIdx)][cornerColIdx];
        State::Player borderPlayer1 = table[cornerRowIdx][cornerAdjacentIdx(cornerColIdx)];

        State::Player diagonalPlayer = table[cornerAdjacentIdx(cornerRowIdx)][cornerAdjacentIdx(cornerColIdx)];

        return getCornerScore(myPlayer, cornerPlayer, { borderPlayer0, borderPlayer1 }, diagonalPlayer);
    }
}

StackPlayerV2::StackPlayerV2() : StackPlayer("StackV2")
{
}

double StackPlayerV2::getHeuristicValueOfState(const State::CPtr& state) const
{
    // Corner score
    const int UPPER_BORDER_IDX = State::TABLE_SIZE - 1;
    State::Player myPlayer = state->getOnMove();
    auto table = state->getTable();
    double cornerScore = getCornerScore(myPlayer, table, 0, 0) + getCornerScore(myPlayer, table, 0, UPPER_BORDER_IDX)
        + getCornerScore(myPlayer, table, UPPER_BORDER_IDX, 0) + getCornerScore(myPlayer, table, UPPER_BORDER_IDX, UPPER_BORDER_IDX);

    // Move score
    auto validMoves = state->getValidMoves();
    int myMoveCount = validMoves.size();
    int opponentMoveCount = state->applyMoveAssumeValid(*validMoves.begin())->getValidMoves().size();
    int moveCountDiff = myMoveCount - opponentMoveCount;
    double moveCountScore = moveCountDiff / 100.0;

    // Calculate score by cornerScore >> moveCountScore (relying on the fact that cornerScore >= 0.01, moveCountScore < 1.0)
    double rawScore = cornerScore + 0.01 * moveCountScore;

    bool currentPlayerIsMaximizer = state->getOnMove() == State::Player::P1;
    double score = currentPlayerIsMaximizer ? rawScore : -rawScore;

    score = std::max(std::min(score, 1.0), -1.0);
    return score;
}

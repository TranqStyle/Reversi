#include "StackPlayer.h"

#include <optional>
#include <algorithm>

using namespace StackAI;

namespace
{
    std::string personalOutcome2string(AbstractPlayer::PersonalOutcome po)
    {
        switch (po)
        {
            case AbstractPlayer::DEFEAT:  return "Defeat";
            case AbstractPlayer::DRAW:    return "Draw";
            case AbstractPlayer::VICTORY: return "Victory";
            default:                      return "Unrecognized PersonalOutcome";
        }
    }

    template <typename T>
    int sgn(T val)
    {
        return (T(0) < val) - (val < T(0));
    }

    struct MoveAndValue
    {
        Move move;
        double value;
    };
}

StackPlayer::StackPlayer() : AbstractPlayer("Stack")
{
}

StackPlayer::StackPlayer(const std::string& preferedName_) : AbstractPlayer(preferedName_)
{
}

Move StackPlayer::getMove(const State::CPtr& state)
{
    int allPieces = state->countAllPieces();
    size_t maxDepth = 4;
    if (allPieces >= 58)
        maxDepth = 6;
    else if (allPieces >= 50)
        maxDepth = 5;

    double alpha = -2.0;
    double beta = -2.0;
    bool currentPlayerIsMaximizer = state->getOnMove() == State::Player::P1;
    
    std::optional<MoveAndValue> bestMAV;
    auto validMoves = state->getValidMoves();
    for (const auto& currentMove : validMoves)
    {
        auto nextState = state->applyMoveAssumeValid(currentMove);
        double currentValue = getValueOfState(nextState, maxDepth, alpha, beta);

        if (currentPlayerIsMaximizer)
            alpha = std::max(alpha, currentValue);
        else
            beta = std::min(beta, currentValue);

        if (!bestMAV || (bestMAV && bestMAV->value < currentValue))
        {
            bestMAV = { currentMove, currentValue };
        }
    }

    if (!bestMAV)
    {
        throw std::logic_error("No eligible move is found");
    }

    _logger.log("The absolute value of the game " + std::to_string(bestMAV->value));
    return bestMAV->move;
}

void StackPlayer::notifyEndGame(const State::CPtr& state, PersonalOutcome personalOutcome) const
{
    _logger.log("The game ending from my perspective: " + personalOutcome2string(personalOutcome));
}

// Assumptions: Player0 minimizes, Player1 maximizes, values are between [-1.0, 1.0], 0.0 is draw
double StackPlayer::getValueOfState(const State::CPtr& state, size_t remainingDepth, double alpha, double beta) const
{
    auto outcome = state->getOutcome();
    if (outcome != State::Outcome::PENDING)
    {
        if (outcome == State::Outcome::P0WIN)
            return -1.0;
        if (outcome == State::Outcome::DRAW)
            return 0.0;
        if (outcome == State::Outcome::P1WIN)
            return +1.0;
        throw std::logic_error("State is not pending, but no outcome can be determined");
    }

    if (remainingDepth == 0)
    {
        return getHeuristicValueOfState(state);
    }

    bool currentPlayerIsMaximizer = state->getOnMove() == State::Player::P1;
    auto validMoves = state->getValidMoves();

    double bestValue;
    if (currentPlayerIsMaximizer)
    {
        bestValue = -2.0;
        for (const auto& currentMove : validMoves)
        {
            auto nextState = state->applyMoveAssumeValid(currentMove);
            double currentValue = getValueOfState(nextState, remainingDepth - 1, alpha, beta);

            bestValue = std::max(bestValue, currentValue);
            alpha = std::max(alpha, bestValue);
            if (bestValue >= beta)
            {
                break; // beta cutoff
            }
        }
    }
    else
    {
        bestValue = +2.0;
        for (const auto& currentMove : validMoves)
        {
            auto nextState = state->applyMoveAssumeValid(currentMove);
            double currentValue = getValueOfState(nextState, remainingDepth - 1, alpha, beta);

            bestValue = std::min(bestValue, currentValue);
            beta = std::min(beta, bestValue);
            if (bestValue <= alpha)
            {
                break; // alpha cutoff
            }
        }
    }
    return bestValue;
}

double StackPlayer::getHeuristicValueOfState(const State::CPtr& state) const
{
    auto validMoves = state->getValidMoves();

    int myMoveCount = validMoves.size();
    int opponentMoveCount = state->applyMoveAssumeValid(*validMoves.begin())->getValidMoves().size();
    int moveCountDiff = myMoveCount - opponentMoveCount;
    int moveCountScore = std::min(400, moveCountDiff * moveCountDiff) * sgn(moveCountDiff);
 
    double rawScore = moveCountScore / 810.0;

    bool currentPlayerIsMaximizer = state->getOnMove() == State::Player::P1;
    double score = currentPlayerIsMaximizer ? rawScore : -rawScore;

    score = std::max(std::min(score, 1.0), -1.0);
    return score;
}

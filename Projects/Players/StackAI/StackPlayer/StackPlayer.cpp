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

    std::string move2string(const Move& move)
    {
        std::ostringstream oss;
        oss << move;
        return oss.str();
    }

    template <typename T>
    int sgn(T val)
    {
        return (T(0) < val) - (val < T(0));
    }

    char popFirst(std::string& str)
    {
        if (str.empty())
            throw std::runtime_error("String is empty");

        char c = str[0];
        str.erase(0, 1);
        return c;
    }

    std::string playerToString(State::Player player)
    {
        if (player == State::Player::NONE)
            return ".";
        return std::to_string(player);
    }
    State::Player stringToPlayer(const std::string& str)
    {
        if (str == "0") return State::Player::P0;
        if (str == "1") return State::Player::P1;
        if (str == ".") return State::Player::NONE;
        throw std::runtime_error("String cannot be converted to player: " + str);
    }

    std::string serializeState(const State::CPtr& state)
    {
        std::string result;

        State::Table table = state->getTable();
        for (int r = 0; r < State::TABLE_SIZE; ++r)
        {
            for (int c = 0; c < State::TABLE_SIZE; ++c)
            {
                result += playerToString(table[r][c]);
            }
        }

        result += playerToString(state->getOnMove());

        return result;
    }

    State::CPtr deserializeState(std::string str)
    {
        State::Table table(State::TABLE_SIZE, std::vector<State::Player>(State::TABLE_SIZE, State::Player::NONE));
        for (int r = 0; r < State::TABLE_SIZE; ++r)
        {
            for (int c = 0; c < State::TABLE_SIZE; ++c)
            {
                table[r][c] = stringToPlayer(std::string{ popFirst(str) });
            }
        }

        State::Player onMove = stringToPlayer(std::string{ popFirst(str) });

        return State::create(table, onMove);
    }

    struct MoveAndValue
    {
        Move move;
        double value;
    };

    bool isPovGreaterThan(bool maximizer, double lhs, double rhs)
    {
        return maximizer ? (lhs < rhs) : (lhs > rhs);
    }
}

StackPlayer::StackPlayer() : AbstractPlayer("Stack")
{
}

StackPlayer::StackPlayer(const std::string& preferedName_) : AbstractPlayer(preferedName_)
{
}

size_t StackPlayer::getMaxDepth(const State::CPtr& baseState) const
{
    int allPieces = baseState->countAllPieces();

    if (allPieces >= 58)
        return 6;
    else if (allPieces >= 50)
        return 4;
    else
        return 3;
}

bool StackPlayer::isCurrentPlayerMaximizer(const State::CPtr& state)
{
    return state->getOnMove() == State::Player::P1;
}

Move StackPlayer::getMove(const State::CPtr& state_)
{
    /**/ // TODO TEMPORARY
    State::CPtr state = state_;
    std::string stateOverride = "";
    //stateOverride = "..11.....11.....110010.....000.....000..........................0";
    if (!stateOverride.empty())
    {
        state = deserializeState(stateOverride);
        std::cout << "=== OVERRIDE STATE ===\n" << *state << std::endl;
    }
    /**/ // TODO TEMPORARY

    _logger.log(serializeState(state));

    size_t maxDepth = getMaxDepth(state);

    double alpha = -2.0;
    double beta = +2.0;
    bool currentPlayerIsMaximizer = isCurrentPlayerMaximizer(state);
    
    std::optional<MoveAndValue> bestMAV;
    auto validMoves = state->getValidMoves();
    for (const auto& currentMove : validMoves)
    {
        auto nextState = state->applyMoveAssumeValid(currentMove);
        double currentValue = getValueOfState(nextState, maxDepth, alpha, beta, move2string(currentMove));

        if (currentPlayerIsMaximizer)
            alpha = std::max(alpha, currentValue);
        else
            beta = std::min(beta, currentValue);

        if (!bestMAV)
        {
            bestMAV = { currentMove, currentValue };
        }
        else if (isPovGreaterThan(currentPlayerIsMaximizer, bestMAV->value, currentValue))
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
double StackPlayer::getValueOfState(const State::CPtr& state, size_t remainingDepth, double alpha, double beta, const std::string& tracer) const
{
    auto outcome = state->getOutcome();
    if (outcome != State::Outcome::PENDING)
    {
        double terminalValue;
        if (outcome == State::Outcome::P0WIN)
            terminalValue = -1.0;
        else if (outcome == State::Outcome::DRAW)
            terminalValue = 0.0;
        else if (outcome == State::Outcome::P1WIN)
            terminalValue = +1.0;
        else
            throw std::logic_error("State is not pending, but no outcome can be determined");
        
        //_logger.log("[TERM]: " + tracer + " : " + std::to_string(terminalValue));
        return terminalValue;
    }

    if (remainingDepth == 0)
    {
        double heuristicValue = getHeuristicValueOfState(state);

        //_logger.log("[HEUR]: " + tracer + " : " + std::to_string(heuristicValue));
        return heuristicValue;
    }

    bool currentPlayerIsMaximizer = isCurrentPlayerMaximizer(state);
    auto validMoves = state->getValidMoves();

    double bestValue;
    if (currentPlayerIsMaximizer)
    {
        bestValue = -2.0;
        for (const auto& currentMove : validMoves)
        {
            auto nextState = state->applyMoveAssumeValid(currentMove);
            double currentValue = getValueOfState(nextState, remainingDepth - 1, alpha, beta, tracer + move2string(currentMove));

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
            double currentValue = getValueOfState(nextState, remainingDepth - 1, alpha, beta, tracer + move2string(currentMove));

            bestValue = std::min(bestValue, currentValue);
            beta = std::min(beta, bestValue);
            if (bestValue <= alpha)
            {
                break; // alpha cutoff
            }
        }
    }
    
    //_logger.log("[TREE]: " + tracer + " : " + std::to_string(bestValue));
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

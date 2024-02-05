#include "State.h"

#include <stdexcept>
#include <sstream>
#include <map>

namespace
{
    State::Table getEmptyTable()
    {
        State::Table result{ State::TABLE_SIZE, std::vector<State::Player>{State::TABLE_SIZE, State::Player::NONE} };
        for (int r = 0; r < State::TABLE_SIZE; ++r)
        {
            std::vector<State::Player> oneRow;
            for (int c = 0; c < State::TABLE_SIZE; ++c)
            {

            }
        }

        return result;
    }

    std::vector<Position> getDirections()
    {
        std::vector<Position> result;

        for (int rowDelta = -1; rowDelta <= 1; ++rowDelta)
        {
            for (int colDelta = -1; colDelta <= 1; ++colDelta)
            {
                if (rowDelta == 0 && colDelta == 0)
                {
                    continue;
                }

                result.push_back(Position(rowDelta, colDelta));
            }
        }

        return result;
    }

    State::Outcome getWinOutcomeFor(State::Player player)
    {
        switch (player)
        {
        case State::Player::P0: return State::Outcome::P0WIN;
        case State::Player::P1: return State::Outcome::P1WIN;
        case State::Player::NONE: return State::Outcome::DRAW;
        default: throw std::runtime_error("Unknown player");
        }
    }
}

const std::vector<Position> State::s_directions = getDirections();

State::Player State::oppositePlayer(Player player)
{
    switch (player)
    {
    case Player::P0: return Player::P1;
    case Player::P1: return Player::P0;
    default: return Player::NONE;
    }
}

State::State()
    : _table(TABLE_SIZE, std::vector<Player>{TABLE_SIZE, State::Player::NONE})
{
    restart();
}

State::State(const State& other) = default;

State::State(const Table& table, Player onMove)
    : _table(table)
    , _onMove(onMove)
    , _outcome(Outcome::PENDING)
    , _consecutivePassCounter(0)
{
    updateOutcome();
}

State::CPtr State::create()
{
    return std::make_shared<const State>();
}

State::CPtr State::create(const State& state)
{
    return std::make_shared<const State>(state);
}

State::CPtr State::create(const Table& table, Player onMove)
{
    return std::make_shared<const State>(table, onMove);
}

void State::restart()
{
    _outcome = Outcome::PENDING;
    _onMove = Player::P0;
    _consecutivePassCounter = 0;
    
    for (auto& oneRow : _table)
    {
        for (auto& tile : oneRow)
        {
            tile = Player::NONE;
        }
    }

    _table[3][3] = Player::P1;
    _table[3][4] = Player::P0;
    _table[4][3] = Player::P0;
    _table[4][4] = Player::P1;
}

State::Player State::getOnMove() const
{
    return _onMove;
}

State::Table State::getTable() const
{
    return _table;
}

State::Outcome State::getOutcome() const
{
    return _outcome;
}

std::set<Move> State::getValidMoves() const
{
    std::set<Move> result;

    for (int r = 0; r < State::TABLE_SIZE; ++r)
    {
        for (int c = 0; c < State::TABLE_SIZE; ++c)
        {
            Position pos{ r, c };
            if (isPositionValidForMove(pos))
            {
                result.insert(Move(pos));
            }
        }
    }

    if (result.empty())
    {
        result.insert(Move{}); // If there are no available moves, then pass is the only move
    }

    return result;
}

State::CPtr State::applyMove(const Move& move) const
{
    State::Ptr newState = std::make_shared<State>(*this);
    newState->applyMove(move);
    return newState;
}

void State::applyMove(const Move& move)
{
    if (getValidMoves().count(move) == 0)
    {
        std::ostringstream oss;
        oss << "Cannot apply invalid move: " << move;
        throw std::runtime_error(oss.str());
    }

    applyMoveAssumeValid(move);
}

State::CPtr State::applyMoveAssumeValid(const Move& move) const
{
    State::Ptr newState = std::make_shared<State>(*this);
    newState->applyMoveAssumeValid(move);
    return newState;
}

void State::applyMoveAssumeValid(const Move& move)
{
    if (move.isPass())
    {
        ++_consecutivePassCounter;
    }
    else
    {
        executeFlip(move.getPosition());
        _consecutivePassCounter = 0;
    }

    _onMove = oppositePlayer(_onMove);

    updateOutcome();
}

void State::updateOutcome()
{
    std::vector<Player> players = { Player::P0, Player::P1 };

    std::map<Player, int> pieceCount;
    for (Player player : players)
    {
        pieceCount[player] = countPiecesForPlayer(player); // TODO This can be tracked, if required
    }

    for (Player player : players)
    {
        if (countPiecesForPlayer(player) == 0)
        {
            _outcome = getWinOutcomeFor(oppositePlayer(player));
            return;
        }
    }

    if (pieceCount[Player::P0] + pieceCount[Player::P1] == TABLE_SIZE * TABLE_SIZE || _consecutivePassCounter >= 2)
    {
        if (pieceCount[Player::P0] > pieceCount[Player::P1])
        {
            _outcome = getWinOutcomeFor(Player::P0);
            return;
        }
        else if (pieceCount[Player::P0] < pieceCount[Player::P1])
        {
            _outcome = getWinOutcomeFor(Player::P1);
            return;
        }
        else
        {
            _outcome = Outcome::DRAW;
            return;
        }
    }
}

void State::executeFlip(const Position& pos)
{
    std::unordered_set<Position> flips = getFlips(pos);

    if (flips.empty())
    {
        std::ostringstream oss;
        oss << "Cannot execute flip at " << pos << ": no pieces would be flipped";
        throw std::logic_error(oss.str());
    }

    _table[pos.getRow()][pos.getCol()] = _onMove;
    for (const Position& flipPos : flips)
    {
        _table[flipPos.getRow()][flipPos.getCol()] = _onMove;
    }
}

bool State::isPositionValidForMove(const Position& pos) const
{
    if (!isOnEmpty(pos))
        return false;

    for (const Position& direction : s_directions)
    {
        std::unordered_set<Position> flipsInDirection = getFlipsInDirection(pos, direction);
        if (!flipsInDirection.empty())
            return true;
    }

    return false;
}

std::unordered_set<Position> State::getFlips(const Position& pos) const
{
    std::unordered_set<Position> result{};

    if (!isOnEmpty(pos))
    {
        return result;
    }


    for (const Position& direction : s_directions)
    {
        std::unordered_set<Position> flipsInDirection = getFlipsInDirection(pos, direction);
        result.merge(flipsInDirection);
    }

    return result;
}

std::unordered_set<Position> State::getFlipsInDirection(const Position& pos, const Position& direction) const
{
    std::unordered_set<Position> potentialFlipPieces{};
    Player friendPiece = _onMove;
    Player enemyPiece = oppositePlayer(friendPiece);

    Position currentPos = pos + direction;
    Player newPiece;
    while ((newPiece = getPieceAtPosition(currentPos)) == enemyPiece)
    {
        potentialFlipPieces.insert(currentPos);
        currentPos = currentPos + direction;
    }

    if (newPiece == friendPiece)
    {
        return potentialFlipPieces;
    }
    else
    {
        return {};
    }
}

bool State::isOnEmpty(const Position& pos) const
{
    if (!isOnTable(pos))
    {
        return false;
    }

    return _table[pos.getRow()][pos.getCol()] == Player::NONE;
}

bool State::isOnBoundary(const Position& pos) const
{
    int row = pos.getRow();
    int col = pos.getCol();
    return (0 == row || row == TABLE_SIZE - 1) && (0 == col || col == TABLE_SIZE - 1);
}

bool State::isOnTable(const Position& pos) const
{
    int row = pos.getRow();
    int col = pos.getCol();
    return (0 <= row && row <= TABLE_SIZE - 1) && (0 <= col && col <= TABLE_SIZE - 1);
}

State::Player State::getPieceAtPosition(const Position& pos) const
{
    if (!isOnTable(pos))
    {
        return Player::NONE; // This could potentially be marked as "out of bounds" Player enum value, but it doesn't seem to be relevant
    }

    return _table[pos.getRow()][pos.getCol()];
}

int State::countPiecesForPlayer(Player player) const
{
    int result = 0;

    for (int r = 0; r < State::TABLE_SIZE; ++r)
    {
        for (int c = 0; c < State::TABLE_SIZE; ++c)
        {
            if (getPieceAtPosition(Position(r, c)) == player)
            {
                result += 1;
            }
        }
    }

    return result;
}

int State::countAllPieces() const
{
    int result = 0;

    for (int r = 0; r < State::TABLE_SIZE; ++r)
    {
        for (int c = 0; c < State::TABLE_SIZE; ++c)
        {
            if (getPieceAtPosition(Position(r, c)) != State::Player::NONE)
            {
                result += 1;
            }
        }
    }

    return result;
}

std::ostream& operator<<(std::ostream& os, State::Outcome outcome)
{
    switch (outcome)
    {
    case State::Outcome::DRAW:
        os << "draw";
        break;
    case State::Outcome::P0WIN:
        os << State::Player::P0 << " won";
        break;
    case State::Outcome::P1WIN:
        os << State::Player::P1 << " won";
        break;
    case State::Outcome::PENDING:
        os << "pending";
        break;
    default:
        os << "unknown";
        break;
    }

    return os;
}

std::ostream& operator<<(std::ostream& os, State::Player player)
{
    switch (player)
    {
    case State::Player::P0:
        os << 'O';
        break;
    case State::Player::P1:
        os << 'X';
        break;
    default:
        os << ' ';
        break;
    }

    return os;
}

std::ostream& operator<<(std::ostream& os, const State& state)
{
    const std::string rowHeader = "  | a | b | c | d | e | f | g | h | ";
    const std::string rowHeaderSeparator = "  +---+---+---+---+---+---+---+---+ ";

    os << '\n';
    os << rowHeader << '\n';
    os << rowHeaderSeparator << '\n';

    for (int r = 0; r < State::TABLE_SIZE; ++r)
    {
        const auto& oneRow = state._table[r];
        int rowLabel = 8 - r;
        os << rowLabel;
        for (const auto& player : oneRow)
        {
            os << " | " << player;
        }
        os << " | " << rowLabel << '\n';
        os << rowHeaderSeparator << '\n';
    }

    os << rowHeader << '\n';
    os << '\n';

    os << "Score:\n";
    for (auto player : { State::Player::P0 , State::Player::P1 })
    {
        os << '\t' << player << ": " << state.countPiecesForPlayer(player) << '\n';
    }
    os << '\n';
    
    os << "Player to move: " << state._onMove << '\n';
    
    if (state._outcome != State::Outcome::PENDING)
    {
        os << "The game is over. Outcome: " << state._outcome << '\n';
    }

    os << std::endl;

    return os;
}

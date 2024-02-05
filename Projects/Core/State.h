#ifndef STATE_H
#define STATE_H

#include "Logger.h"
#include "Move.h"

#include <memory>
#include <string>
#include <vector>
#include <set>
#include <unordered_set>
#include <iostream>

class State
{
public:
    typedef std::shared_ptr<const State> CPtr;
    typedef std::shared_ptr<State> Ptr;

    enum class Outcome { PENDING, P0WIN, P1WIN, DRAW };
    enum Player { NONE = -1, P0 = 0, P1 = 1 }; // This can be used as int
    static Player oppositePlayer(Player player);

    static constexpr int TABLE_SIZE = 8;
    using Table = std::vector<std::vector<Player>>;

    State();
    State(const State& other);
    State(const Table& table, Player onMove);

    static CPtr create();
    static CPtr create(const State& other);
    static CPtr create(const Table& table, Player onMove);

    void restart(); // Initialize to new game state
    Player getOnMove() const;
    Table getTable() const; // TODO: This might need to be returned by ref
    Outcome getOutcome() const;

    std::set<Move> getValidMoves() const;
    CPtr applyMove(const Move& move) const; //! Throws in case of invalid move
    void applyMove(const Move& move); //! Throws in case of invalid move
    CPtr applyMoveAssumeValid(const Move& move) const; //! Places a piece on move's position (potentially disregarding rules) - only use this, if you can guarantee that move is valid
    void applyMoveAssumeValid(const Move& move); //! Places a piece on move's position (potentially disregarding rules) - only use this, if you can guarantee that move is valid

    int countPiecesForPlayer(Player player) const;
    int countAllPieces() const;

    friend std::ostream& operator<<(std::ostream& os, const State& state); // It is a GUI version

private:
    static const std::vector<Position> s_directions;

    Table _table; // i. e. _table[1][7] = Player::{NONE|P1|P2} --> means (1, 7) is occupied by {Noone|1st Player|2nd Player}
    Player _onMove; // 0 means first player, 1 means second player
    Outcome _outcome;
    int _consecutivePassCounter;

    void updateOutcome();
    void executeFlip(const Position& pos);

    bool isPositionValidForMove(const Position& pos) const;
    std::unordered_set<Position> getFlips(const Position& pos) const;
    std::unordered_set<Position> getFlipsInDirection(const Position& pos, const Position& dir) const; //! Assumes that pos is empty and dir is a valid direction

    bool isOnEmpty(const Position& pos) const;
    bool isOnBoundary(const Position& pos) const;
    bool isOnTable(const Position& pos) const;

    Player getPieceAtPosition(const Position& pos) const;
};

std::ostream& operator<<(std::ostream& os, State::Outcome outcome);
std::ostream& operator<<(std::ostream& os, State::Player player);

#endif // STATE_H


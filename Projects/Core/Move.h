#ifndef MOVE_H
#define MOVE_H

#include "Position.h"
#include <optional>
#include <iostream>

class Move
{
public:
    explicit Move(const std::optional<Position>& position = {});
    
    bool isPass() const;
    Position getPosition() const;
    
    size_t getHash() const;
    friend bool operator==(const Move& lhs, const Move& rhs);
    friend bool operator!=(const Move& lhs, const Move& rhs);
    friend bool operator< (const Move& lhs, const Move& rhs); // asc by `row` THEN asc by `col`, pass first
    friend bool operator> (const Move& lhs, const Move& rhs);
    friend std::ostream& operator<<(std::ostream& os, const Move& move);
    
private:
    std::optional<Position> _position;
};

template<> struct std::hash<Move>
{
    std::size_t operator()(const Move& move) const noexcept
    {
        return move.getHash();
    }
};

#endif // MOVE_H

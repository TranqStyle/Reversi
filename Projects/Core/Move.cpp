#include "Move.h"

#include <stdexcept>

Move::Move(const std::optional<Position>& position)
    : _position(position)
{
}

bool Move::isPass() const
{
    return !_position.has_value();
}

Position Move::getPosition() const
{
    if (_position)
    {
        return *_position;
    }
    else
    {
        throw std::runtime_error("Move is a pass, it does not have a position");
    }
}

size_t Move::getHash() const
{
    if (isPass())
    {
        return 1000000; // TODO Hack
    }
    else
    {
        return _position->getHash();
    }
}

bool operator==(const Move& lhs, const Move& rhs)
{
    return lhs._position == rhs._position;
}

bool operator!=(const Move& lhs, const Move& rhs)
{
    return !(lhs == rhs);
}

bool operator<(const Move& lhs, const Move& rhs)
{
    return lhs._position < rhs._position;
}

bool operator>(const Move& lhs, const Move& rhs)
{
    return rhs < lhs;
}

std::ostream& operator<<(std::ostream& os, const Move& move)
{
    if (move.isPass())
    {
        os << "[Pass]";
    }
    else
    {
        os << move.getPosition();
    }
    
    return os;
}

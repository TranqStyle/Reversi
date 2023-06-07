#include "Position.h"

#include <iostream>

Position::Position(int row, int col)
    : _row(row)
    , _col(col)
{
}

int Position::getRow() const
{
    return _row;
}

int Position::getCol() const
{
    return _col;
}

size_t Position::getHash() const
{
    return _row + 1000 * _col; // TODO Hack
}

bool operator==(const Position& lhs, const Position& rhs)
{
    return lhs._row == rhs._row &&
           lhs._col == rhs._col;
}

bool operator!=(const Position& lhs, const Position& rhs)
{
    return !(lhs == rhs);
}

bool operator<(const Position& lhs, const Position& rhs)
{
    if (lhs._row < rhs._row)
        return true;
    
    if (lhs._row > rhs._row)
        return false;
    
    if (lhs._col < rhs._col)
        return true;
    
    if (lhs._col > rhs._col)
        return false;
    
    return false; // They are equal
}

bool operator>(const Position& lhs, const Position& rhs)
{
    return rhs < lhs;
}

Position operator+(const Position& lhs, const Position& rhs)
{
    return Position(lhs._row + rhs._row, lhs._col + rhs._col);
}

std::ostream& operator<<(std::ostream& os, const Position& pos)
{
    os << "(" << pos._row << ", " << pos._col << ")";
    
    return os;
}

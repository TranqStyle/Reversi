#ifndef POSITION_H
#define POSITION_H

#include <iostream>

class Position
{
public:
    Position(int row, int col);

    int getRow() const;
    int getCol() const;
    
    size_t getHash() const;
    friend bool operator==(const Position& lhs, const Position& rhs);
    friend bool operator!=(const Position& lhs, const Position& rhs);
    friend bool operator< (const Position& lhs, const Position& rhs); // asc by `row` THEN asc by `col`
    friend bool operator> (const Position& lhs, const Position& rhs);
    friend Position operator+(const Position& lhs, const Position& rhs);
    friend std::ostream& operator<<(std::ostream& os, const Position& pos);
    
private:
    int _row;
    int _col;
};

template<> struct std::hash<Position>
{
    std::size_t operator()(const Position& position) const noexcept
    {
        return position.getHash();
    }
};

#endif // POSITION_H

#include "TranqUtil.h"

bool TranqUtil::isOnCorner(const Position& pos) {
    int row = pos.getRow();
    int col = pos.getCol();
    return ((row == 0 || row == State::TABLE_SIZE - 1) && (col == 0 || col == State::TABLE_SIZE - 1));
}

bool TranqUtil::isOnBoundary(const Position& pos) {
    int row = pos.getRow();
    int col = pos.getCol();
    return ((row == 0 || row == State::TABLE_SIZE - 1) || (col == 0 || col == State::TABLE_SIZE - 1));
}

bool TranqUtil::isOnBuffer(const Position& pos) {
    int row = pos.getRow();
    int col = pos.getCol();
    return ((row == 0 && (col == 1 || col == 6)) || (row == 1 && (col == 0 || col == 1 || col == 6 || col == 7))
        || (row == 6 && (col == 0 || col == 1 || col == 6 || col == 7)) || (row == 7 && (col == 1 || col == 6)));
}

bool TranqUtil::isOnBufferExtended(const Position& pos) {
    int row = pos.getRow();
    int col = pos.getCol();
    return (((row == 1 || row == 6) && (col == 2 || col == 3 || col == 4 || col == 5))
        || ((col == 1 || col == 6) && (row == 2 || row == 3 || row == 4 || row == 5)));
}

bool TranqUtil::isVectorOnBuffer(const std::vector<Move>& moves) {
    int vectorLength = moves.size();
    int movesOnBuffer{ 0 };
    for (const auto& move : moves) {
        if (isOnBuffer(move.getPosition())) {
            movesOnBuffer++;
        }
    }
    return (vectorLength == movesOnBuffer ? true : false);
}

double TranqUtil::normalizeNumber(const double& num, const double& numMin, const double& numMax) {
    return (num - numMin) / (numMax - numMin);
}
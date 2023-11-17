#include "MoveEvaluation.h"
#include "TranqUtil.h"
#include "Utility.h"


MoveEvaluation::MoveEvaluation(const std::vector<MoveWithMetrics>& moveVector)
{
    if (moveVector.size() > 0) {
        _moveList = moveVector;
        _moveListSize = moveVector.size();
    }
    else {
        throw std::invalid_argument{ "Vector must not be empty!" };
    }
}

size_t MoveEvaluation::getMoveListSize() const{
    return _moveListSize;
}

std::vector<MoveWithMetrics> MoveEvaluation::getMoveList() const {
    return _moveList;
}

std::vector<MoveWithMetrics> MoveEvaluation::calculateNMovesCapture(const size_t& n) {
    size_t resultsSize{ 0 };
    std::vector<MoveWithMetrics> moveList = getMoveList();
    size_t moveListSize = getMoveListSize();
    State::CPtr st = moveList[0].getState();
    if (moveListSize >= n) {
        resultsSize = n;
    }
    else {
        resultsSize = moveListSize;
    }
    std::vector<MoveWithMetrics> results{ resultsSize, MoveWithMetrics{st, Move{}} };
    for (const MoveWithMetrics& move : moveList) {
        Move mv = move.getMove();
        int moveToken = move.getTokenAmount();
        for (size_t i{ 0 }; i < resultsSize; ++i) {
            if (moveToken > results[i].getTokenAmount()) {
                for (size_t j{ resultsSize - 1 }; j >= i + 1; --j) {
                    results[j] = results[j - 1];
                }
                results[i] = move;
                break;
            }
            else if (moveToken == results[i].getTokenAmount()) {
                for (size_t j{ resultsSize - 1 }; j >= i + 2; --j) {
                    results[j] = results[j - 1];
                }
                std::vector<Move> tieMoves{ results[i].getMove(), mv };
                size_t totalPiecesOnBoard = st->countPiecesForPlayer(State::Player::P0) + st->countPiecesForPlayer(State::Player::P1);
                Move betterMove = tiebreak(tieMoves, totalPiecesOnBoard);
                if (i == resultsSize - 1 && betterMove == mv) {
                    results[i] = move;
                }
                else if (betterMove == results[i].getMove() && i != resultsSize - 1) {
                    results[i + 1] = move;
                }
                else if (betterMove == mv && i != resultsSize - 1) {
                    results[i + 1] = results[i];
                    results[i] = move;
                }
                break;
            }
        }
    }
    return results;
}

std::vector<MoveWithMetrics> MoveEvaluation::calculateNMovesMobility(const size_t& n) {
    size_t resultsSize{ 0 };
    std::vector<MoveWithMetrics> moveList = getMoveList();
    size_t moveListSize = getMoveListSize();
    State::CPtr st = moveList[0].getState();
    if (moveListSize >= n) {
        resultsSize = n;
    }
    else {
        resultsSize = moveListSize;
    }
    std::vector<MoveWithMetrics> results{ resultsSize, MoveWithMetrics{st, Move{}} };
    for (const MoveWithMetrics& move : moveList) {
        Move mv = move.getMove();
        size_t moveMobility = move.getMobility();
        for (size_t i{ 0 }; i < resultsSize; ++i) {
            if (moveMobility < results[i].getMobility()) {
                for (size_t j{ resultsSize - 1 }; j >= i + 1; --j) {
                    results[j] = results[j - 1];
                }
                results[i] = move;
                break;
            }
            else if (moveMobility == results[i].getMobility()) {
                for (size_t j{ resultsSize - 1 }; j >= i + 2; --j) {
                    results[j] = results[j - 1];
                }
                std::vector<Move> tieMoves{ results[i].getMove(), mv };
                size_t totalPieceCount = st->countPiecesForPlayer(State::Player::P0) + st->countPiecesForPlayer(State::Player::P1);
                Move betterMove = tiebreak(tieMoves, totalPieceCount);
                if (i == resultsSize - 1 && betterMove == mv) {
                    results[i] = move;
                }
                else if (betterMove == results[i].getMove() && i != resultsSize - 1) {
                    results[i + 1] = move;
                }
                else if (betterMove == mv && i != resultsSize - 1) {
                    results[i + 1] = results[i];
                    results[i] = move;
                }
                break;
            }
        }
    }
    return results;
}

std::vector<MoveWithMetrics> MoveEvaluation::calculateNMovesMixed(const size_t& n) {
    size_t resultsSize{ 0 };
    std::vector<MoveWithMetrics> moveList = getMoveList();
    size_t moveListSize = getMoveListSize();
    State::CPtr st = moveList[0].getState();
    if (moveListSize >= n) {
        resultsSize = n;
    }
    else {
        resultsSize = moveListSize;
    }
    std::vector<MoveWithMetrics> results{ resultsSize, MoveWithMetrics{st, Move{}} };
    for (const MoveWithMetrics& move : moveList) {
        Move mv = move.getMove();
        Position pos = mv.getPosition();
        double moveMixedMetric = move.getMixedMetric();
        size_t totalPieceCount = st->countPiecesForPlayer(State::Player::P0) + st->countPiecesForPlayer(State::Player::P1);
        for (size_t i{ 0 }; i < resultsSize; ++i) {
            if (moveMixedMetric > results[i].getMixedMetric()) {
                for (size_t j{ resultsSize - 1 }; j >= i + 1; --j) {
                    results[j] = results[j - 1];
                }
                results[i] = move;
                break;
            }
            else if (moveMixedMetric == results[i].getMixedMetric()) {
                for (size_t j{ resultsSize - 1 }; j >= i + 2; --j) {
                    results[j] = results[j - 1];
                }
                Move betterMove = tiebreakMixed(mv, results[i].getMove());
                if (i == resultsSize - 1 && betterMove == mv) {
                    results[i] = move;
                }
                else if (betterMove == results[i].getMove() && i != resultsSize - 1) {
                    results[i + 1] = move;
                }
                else if (betterMove == mv && i != resultsSize - 1) {
                    results[i + 1] = results[i];
                    results[i] = move;
                }
                break;
            }
        }
    }
    return results;
}

Move MoveEvaluation::tiebreakMixed(const Move& first, const Move& second) {
    TranqUtil tUtil;
    if (tUtil.isOnCorner(first.getPosition()) && tUtil.isOnCorner(second.getPosition())
        || (tUtil.isOnBoundary(first.getPosition()) && tUtil.isOnBoundary(second.getPosition()))
        || (tUtil.isOnBufferExtended(first.getPosition()) && tUtil.isOnBuffer(second.getPosition()))
        || (tUtil.isOnBuffer(first.getPosition()) && tUtil.isOnBuffer(second.getPosition()))) {
        Utility util;
        std::vector<Move> moveVector{ first, second };
        return util.selectRandomElement(moveVector);
    }
    else if ((tUtil.isOnCorner(first.getPosition()) && !tUtil.isOnCorner(second.getPosition()))
        || (tUtil.isOnBoundary(first.getPosition()) && !tUtil.isOnBoundary(second.getPosition()))
        || (tUtil.isOnBufferExtended(first.getPosition()) && !tUtil.isOnBuffer(second.getPosition()))
        || (tUtil.isOnBuffer(first.getPosition()) && !tUtil.isOnBuffer(second.getPosition()))) {
        return first;
    }
    else if ((!tUtil.isOnCorner(first.getPosition()) && tUtil.isOnCorner(second.getPosition()))
        || (!tUtil.isOnBoundary(first.getPosition()) && tUtil.isOnBoundary(second.getPosition()))
        || (!tUtil.isOnBufferExtended(first.getPosition()) && tUtil.isOnBuffer(second.getPosition()))
        || (!tUtil.isOnBuffer(first.getPosition()) && tUtil.isOnBuffer(second.getPosition()))) {
        return second;
    }
    else {
        Utility util;
        std::vector<Move> moveVector{ first, second };
        return util.selectRandomElement(moveVector);
    }
}

Move MoveEvaluation::tiebreak(const std::vector<Move>& movesList, const size_t& totalPieces) {
    std::vector<Move> movesOnCorner{};
    std::vector<Move> movesOnBoundary{};
    std::vector<Move> otherMoves{};
    const int bufferCutOff{ 24 };
    Utility util;
    TranqUtil tUtil;

    for (auto it = movesList.cbegin(); it != movesList.cend(); ++it) {
        if (tUtil.isOnCorner(it->getPosition())) {
            movesOnCorner.push_back(*it);
        }
        else if (tUtil.isOnBoundary(it->getPosition())) {
            movesOnBoundary.push_back(*it);
        }
        else {
            otherMoves.push_back(*it);
        }
    }

    if (movesOnCorner.size() != 0) {
        return util.selectRandomElement(movesOnCorner);
    }
    else if (movesOnBoundary.size() != 0) {
        if (!tUtil.isVectorOnBuffer(movesOnBoundary)) {
            Move randomMove = util.selectRandomElement(movesOnBoundary);
            while (tUtil.isOnBuffer(randomMove.getPosition()) && totalPieces <= bufferCutOff) {
                randomMove = util.selectRandomElement(movesOnBoundary);
            }
            return randomMove;
        }
        else {
            return util.selectRandomElement(movesOnBoundary);
        }
    }
    else {
        Move randomMove = util.selectRandomElement(otherMoves);
        if (!tUtil.isVectorOnBuffer(otherMoves)) {
            while (tUtil.isOnBuffer(randomMove.getPosition()) && totalPieces <= bufferCutOff) {
                randomMove = util.selectRandomElement(otherMoves);
            }
        }
        return randomMove;
    }
}
#ifndef MOVEEVALUATION_H
#define MOVEEVALUATION_H

#include "MoveWithMetrics.h"
#include "State.h"

class MoveEvaluation {
public:
    MoveEvaluation(const std::vector<MoveWithMetrics>&);

    std::vector<MoveWithMetrics> calculateNMovesCapture(const size_t&);
    std::vector<MoveWithMetrics> calculateNMovesMobility(const size_t&);
    std::vector<MoveWithMetrics> calculateNMovesMixed(const size_t&);

    size_t getMoveListSize() const;
    std::vector<MoveWithMetrics> getMoveList() const;
    
    Move tiebreak(const std::vector<Move>&, const size_t&);
    Move tiebreakMixed(const Move&, const Move&);


private:
    std::vector<MoveWithMetrics> _moveList{};
    size_t _moveListSize;
};
#endif
#ifndef TRANQUTIL_CPP
#define TRANQUTIL_CPP

#include "State.h"

class TranqUtil {

public:
    bool isOnCorner(const Position&);
    bool isOnBoundary(const Position&);
    bool isOnBuffer(const Position&);
    bool isOnBufferExtended(const Position&);
    bool isVectorOnBuffer(const std::vector<Move>&);
    double normalizeNumber(const double&, const double&, const double&);
};

#endif
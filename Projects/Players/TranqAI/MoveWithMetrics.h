#ifndef MOVEWITHMETRICS_H
#define MOVEWITHMETRICS_H

#include "State.h"


class MoveWithMetrics {
public:
    MoveWithMetrics(const State::CPtr&, const Move & = Move{}, const double& = 0.40, const double& = 0.60);
    explicit MoveWithMetrics(const MoveWithMetrics& cpy) = default;

    MoveWithMetrics& operator=(const MoveWithMetrics& rhs) {
        _move = rhs.getMove();
        _state = rhs.getState();
        _myPlayer = rhs.getPlayer();
        _newState = rhs.getNewState();
        _mixedMetric = rhs.getTokenWeight();
        _mobilityWeight = rhs.getMobilityWeight();
        _tokenAmount = rhs.getTokenAmount();
        _mobility = rhs.getMobility();
        _tokenNormalized = rhs.getTokenNormalized();
        _mobilityNormalized = rhs.getMobilityNormalized();
        _mixedMetric = rhs.getMixedMetric();
        return *this;
    }

    int calculateTokenAmount(); 
    size_t calculateMobility();
    double calculateMixedMetric();
    void setMixedMetric(const double&);
    double getMixedMetric() const;
    void setMove(const Move&);
    Move getMove() const;
    void setTokenWeight(const double&);
    double getTokenWeight() const;
    void setMobilityWeight(const double&);
    double getMobilityWeight() const;
    void setState(const State::CPtr&);
    State::CPtr getState() const;
    void setNewState(const State::CPtr&);
    State::CPtr getNewState() const;
    void setTokenAmount(const int&);
    int getTokenAmount() const;
    void setTokenNormalized(const double&);
    double getTokenNormalized() const;
    void setMobility(const size_t&);
    size_t getMobility() const;
    void setMobilityNormalized(const double&);
    double getMobilityNormalized() const;
    void setPlayer(const State::Player&);
    State::Player getPlayer() const;

private:
    const double minTokenAmount{ 0.0 };
    const double maxTokenAmount{ 19.0 };
    const double minMobility{ 0.0 };
    const double maxMobility{ 24.0 };
    const int bufferCutOff{ 24 };
    const int extendedBufferCutOff{ 13 };
    
    Move _move;
    int _tokenAmount;
    double _tokenWeight;
    double _tokenNormalized;
    size_t _mobility;
    double _mobilityWeight;
    double _mobilityNormalized;
    double _mixedMetric;
    State::CPtr _state;
    State::CPtr _newState;
    State::Player _myPlayer;
};

#endif
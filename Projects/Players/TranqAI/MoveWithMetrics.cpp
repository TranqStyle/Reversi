#include "MoveWithMetrics.h"
#include "TranqUtil.h"


MoveWithMetrics::MoveWithMetrics(const State::CPtr& state, const Move& move,
    const double& tokenWeight, const double& mobilityWeight)
    : _move{ move }, _state{ state }, _myPlayer{ _state->getOnMove() },
    _tokenWeight{ tokenWeight }, _mobilityWeight{ mobilityWeight }
{
    if (_move == Move{}) {
        _newState = _state ;
        _tokenAmount = -99;
        _mobility = 99;
        _tokenNormalized = minTokenAmount;
        _mobilityNormalized = maxMobility;
        _mixedMetric = -10.0;
    }
    else {
        TranqUtil tUtil;
        _newState = _state->applyMove(_move);
        _tokenAmount = calculateTokenAmount();
        _mobility = calculateMobility();
        _tokenNormalized = tUtil.normalizeNumber(_tokenAmount, minTokenAmount, maxTokenAmount);
        _mobilityNormalized = tUtil.normalizeNumber(_mobility, minMobility, maxMobility);
        _mixedMetric = calculateMixedMetric();
    }
}

int MoveWithMetrics::calculateTokenAmount() {
    return getNewState()->countPiecesForPlayer(getPlayer()) - getState()->countPiecesForPlayer(getPlayer());
}

size_t MoveWithMetrics::calculateMobility() {
    return getNewState()->getValidMoves().size();
}

double MoveWithMetrics::calculateMixedMetric() {
    double baseMixedMetric = getTokenNormalized() * getTokenWeight() + (1.0 - getMobilityNormalized()) * getMobilityWeight();
    int totalPieceCount = getState()->countPiecesForPlayer(State::Player::P0) + getState()->countPiecesForPlayer(State::Player::P1);
    Position pos = getMove().getPosition();
    TranqUtil tUtil;
    if (tUtil.isOnCorner(pos)) {
        baseMixedMetric += 0.15;
    }
    else if (tUtil.isOnBuffer(pos) && totalPieceCount <= bufferCutOff) {
        baseMixedMetric -= 0.15;
    }
    else if (tUtil.isOnBoundary(pos)) {
        baseMixedMetric += 0.10;
    }
    else if (tUtil.isOnBufferExtended(pos) && totalPieceCount <= extendedBufferCutOff) {
        baseMixedMetric -= 0.10;
    }
    return baseMixedMetric;
}

double MoveWithMetrics::getMixedMetric() const {
    return _mixedMetric;
}

void MoveWithMetrics::setMixedMetric(const double& mixedMetric) {
    _mixedMetric = mixedMetric;
}

Move MoveWithMetrics::getMove() const {
    return _move;
}

void MoveWithMetrics::setMove(const Move& move) {
    _move = move;
}

double MoveWithMetrics::getTokenWeight() const {
    return _tokenWeight;
}

void MoveWithMetrics::setTokenWeight(const double& tokenWeight) {
    _tokenWeight = tokenWeight;
}

double MoveWithMetrics::getMobilityWeight() const {
    return _mobilityWeight;
}

void MoveWithMetrics::setMobilityWeight(const double& mobilityWeight) {
    _mobilityWeight = mobilityWeight;
}

State::CPtr MoveWithMetrics::getState() const {
    return _state;
}

void MoveWithMetrics::setState(const State::CPtr& state) {
    _state = state;
}

State::CPtr MoveWithMetrics::getNewState() const {
    return _newState;
}

void MoveWithMetrics::setNewState(const State::CPtr& newState) {
    _newState = newState;
}

int MoveWithMetrics::getTokenAmount() const {
    return _tokenAmount;
}

void MoveWithMetrics::setTokenAmount(const int& tokenAmount) {
    _tokenAmount = tokenAmount;
}

double MoveWithMetrics::getTokenNormalized() const {
    return _tokenNormalized;
}

void MoveWithMetrics::setTokenNormalized(const double& tokenNormalized) {
    _tokenNormalized = tokenNormalized;
}

size_t MoveWithMetrics::getMobility() const {
    return _mobility;
}

void MoveWithMetrics::setMobility(const size_t& mobility) {
    _mobility = mobility;
}

double MoveWithMetrics::getMobilityNormalized() const {
    return _mobilityNormalized;
}

void MoveWithMetrics::setMobilityNormalized(const double& mobilityNormalized) {
    _mobilityNormalized = mobilityNormalized;
}

State::Player MoveWithMetrics::getPlayer() const {
    return _myPlayer;
}

void MoveWithMetrics::setPlayer(const State::Player& player) {
    _myPlayer = player;
}

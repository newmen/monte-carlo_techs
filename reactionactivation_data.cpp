#include <cmath>
#include "reactionactivation_data.h"

ReactionActivationData::ReactionActivationData(const RTReactorContext *reactor, double Ea) :
    _reactor(reactor), _Ea(Ea) {}

double ReactionActivationData::expFactor(double additionalEnergy) const {
    return exp(-(_Ea + additionalEnergy) / _reactor->RT());
}

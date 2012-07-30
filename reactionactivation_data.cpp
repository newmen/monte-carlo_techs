#include <cmath>
#include "reactionactivation_data.h"

ReactionActivationData::ReactionActivationData(const RTReactorContext *reactor, long double Ea) :
    _reactor(reactor), _Ea(Ea) {}

long double ReactionActivationData::expFactor(long double additionalEnergy) const {
    return exp((-_Ea + additionalEnergy) / _reactor->RT());
}

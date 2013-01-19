#include "dimerreactionactivationexplosion_data.h"

DimerReactionActivationExplosionData::DimerReactionActivationExplosionData(int firstPrevState, int secondPrevState, int nextState, long double k, long double Ea, const RTReactorContext *reactor) :
    DimerReactionDualStabilizationData(firstPrevState, secondPrevState, nextState, k), ReactionActivationData(reactor, Ea) {}

long double DimerReactionActivationExplosionData::rateValue(const DimerData *) const {
    return this->k() * expFactor();
}

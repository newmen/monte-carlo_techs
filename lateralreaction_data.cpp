#include "lateralreaction_data.h"

LateralReactionData::LateralReactionData(const RTReactorContext *reactor, long double Ea, long double epss[], int numOfSpecs) :
    ReactionActivationData(reactor, Ea), _numOfSpecs(numOfSpecs)
{
    _epss = new long double[_numOfSpecs];
    for (int i = 0; i < _numOfSpecs; ++i) _epss[i] = epss[i];
}

LateralReactionData::~LateralReactionData() {
    delete [] _epss;
}

long double LateralReactionData::expFactor(const LateralSiteData *site) const {
    long double lateralEnergy = 0;
    for (int i = 0; i < _numOfSpecs; ++i) {
        lateralEnergy += site->numOfSpec(i) * _epss[i];
    }
    return ReactionActivationData::expFactor(lateralEnergy);
}

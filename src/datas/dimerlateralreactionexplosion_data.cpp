#include "dimerlateralreactionexplosion_data.h"
#include "lateraldimer_data.h"

DimerLateralReactionExplosionData::DimerLateralReactionExplosionData(int firstPrevState, int secondPrevState, int nextState, long double k, long double Ea, long double epss[], const RTReactorContext *reactor) :
    DimerReactionDualStabilizationData(firstPrevState, secondPrevState, nextState, k), LateralReactionData(reactor, Ea, epss) {}

long double DimerLateralReactionExplosionData::rateValue(const DimerData *dimer) const {
    const LateralDimerData *lateralDimer = static_cast<const LateralDimerData *>(dimer);
    return this->k() * expFactor(lateralDimer);
}

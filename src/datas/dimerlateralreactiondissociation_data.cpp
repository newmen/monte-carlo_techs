#include "dimerlateralreactiondissociation_data.h"
#include "lateraldimer_data.h"

DimerLateralReactionDissociationData::DimerLateralReactionDissociationData(int emptyState, int dissociatedState, int separatedState, int remainingState, long double k, long double Ea, long double epss[], const RTReactorContext *reactor) :
    DimerReactionDissociationData(emptyState, dissociatedState, separatedState, remainingState, k), LateralReactionData(reactor, Ea, epss) {}

// copypaste :'(
long double DimerLateralReactionDissociationData::rateValue(const DimerData *dimer) const {
    const LateralDimerData *lateralDimer = static_cast<const LateralDimerData *>(dimer);
    return this->k() * expFactor(lateralDimer);
}

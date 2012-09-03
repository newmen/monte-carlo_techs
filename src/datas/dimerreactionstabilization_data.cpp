#include "dimerreactionstabilization_data.h"

DimerReactionStabilizationData::DimerReactionStabilizationData(int prevState, int nextState, long double k) :
    ReactionData<DimerData>(prevState, nextState, k) {}

long double DimerReactionStabilizationData::rate(const DimerData *dimer) const {
    return (dimer->first->value() == prevState() && dimer->second->value() == prevState()) ?
                rateValue(dimer) : 0;
}

void DimerReactionStabilizationData::doIt(DimerData *const dimer) const {
    dimer->first->setValue(nextState());
    dimer->second->setValue(nextState());
}

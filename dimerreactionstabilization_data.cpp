#include "dimerreactionstabilization_data.h"

DimerReactionStabilizationData::DimerReactionStabilizationData(long double k, int prevState, int nextState) :
    ReactionData<DimerData>(k, prevState, nextState) {}

long double DimerReactionStabilizationData::rate(const DimerData *dimer) const {
    return (dimer->first->value() == prevState() && dimer->second->value() == prevState()) ?
                rateValue(dimer) : 0;
}

void DimerReactionStabilizationData::doIt(DimerData *const dimer) const {
    dimer->first->setValue(nextState());
    dimer->second->setValue(nextState());
}

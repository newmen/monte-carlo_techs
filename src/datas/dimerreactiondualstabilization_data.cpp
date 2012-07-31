#include "dimerreactiondualstabilization_data.h"

DimerReactionDualStabilizationData::DimerReactionDualStabilizationData(long double k, int firstPrevState, int secondPrevState, int nextState) :
    ReactionData<DimerData>(k, firstPrevState, nextState), _secondPrevState(secondPrevState) {}

long double DimerReactionDualStabilizationData::rate(const DimerData *dimer) const {
    return ((dimer->first->value() == prevState() && dimer->second->value() == _secondPrevState) ||
            (dimer->first->value() == _secondPrevState && dimer->second->value() == prevState())) ?
                rateValue(dimer) : 0;
}

void DimerReactionDualStabilizationData::doIt(DimerData *const dimer) const {
    dimer->first->setValue(nextState());
    dimer->second->setValue(nextState());
}

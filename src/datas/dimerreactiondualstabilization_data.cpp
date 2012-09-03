#include "dimerreactiondualstabilization_data.h"

DimerReactionDualStabilizationData::DimerReactionDualStabilizationData(int firstPrevState, int secondPrevState, int nextState, long double k) :
    ReactionData<DimerData>(firstPrevState, nextState, k), _secondPrevState(secondPrevState) {}

long double DimerReactionDualStabilizationData::rate(const DimerData *dimer) const {
    return ((dimer->first->value() == prevState() && dimer->second->value() == _secondPrevState) ||
            (dimer->first->value() == _secondPrevState && dimer->second->value() == prevState())) ?
                rateValue(dimer) : 0;
}

void DimerReactionDualStabilizationData::doIt(DimerData *const dimer) const {
    dimer->first->setValue(nextState());
    dimer->second->setValue(nextState());
}

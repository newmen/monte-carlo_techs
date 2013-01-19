#include "dimerreactiondissociation_data.h"

DimerReactionDissociationData::DimerReactionDissociationData(int emptyState, int dissociatedState, int separatedState, int remainingState, long double k) : ReactionData<DimerData>(emptyState, dissociatedState, k), _separatedState(separatedState), _remainingState(remainingState) {}

long double DimerReactionDissociationData::rate(const DimerData *dimer) const {
    return ((dimer->first->value() == prevState() && dimer->second->value() == nextState()) ||
            (dimer->first->value() == nextState() && dimer->second->value() == prevState())) ?
                rateValue(dimer) : 0;
}

void DimerReactionDissociationData::doIt(DimerData *const dimer) const {
    if (dimer->first->value() == prevState() && dimer->second->value() == nextState()) {
        dimer->first->setValue(_separatedState);
        dimer->second->setValue(_remainingState);
    } else {
        dimer->first->setValue(_remainingState);
        dimer->second->setValue(_separatedState);
    }
}



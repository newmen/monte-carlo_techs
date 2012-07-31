#include "dimerreactionexchange_data.h"

DimerReactionExchangeData::DimerReactionExchangeData(long double k, int prevState, int nextState) :
    ReactionData<DimerData>(k, prevState, nextState) {}

long double DimerReactionExchangeData::rate(const DimerData *dimer) const {
    return ((dimer->first->value() == nextState() && dimer->second->value() == prevState()) ||
            (dimer->first->value() == prevState() && dimer->second->value() == nextState())) ?
                rateValue(dimer) : 0;
}

void DimerReactionExchangeData::doIt(DimerData *const dimer) const {
    if (dimer->first->value() == nextState()) {
        dimer->first->setValue(prevState());
        dimer->second->setValue(nextState());
    } else {
        dimer->first->setValue(nextState());
        dimer->second->setValue(prevState());
    }
}

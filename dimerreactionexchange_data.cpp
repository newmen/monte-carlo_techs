#include "dimerreactionexchange_data.h"

DimerReactionExchangeData::DimerReactionExchangeData(double rateValue, int prevState, int nextState) :
    ReactionData<DimerData>(rateValue, prevState, nextState) {}

double DimerReactionExchangeData::rate(const DimerData &dimer) const {
    return ((dimer.first->value() == this->nextState() && dimer.second->value() == this->prevState()) ||
            (dimer.first->value() == this->prevState() && dimer.second->value() == this->nextState())) ?
                this->k() : 0;
}

void DimerReactionExchangeData::doIt(DimerData *const dimer) const {
    if (dimer->first->value() == this->nextState()) {
        dimer->first->setValue(this->prevState());
        dimer->second->setValue(this->nextState());
    } else {
        dimer->first->setValue(this->nextState());
        dimer->second->setValue(this->prevState());
    }
}

#include "dimerreactionstabilization_data.h"

DimerReactionStabilizationData::DimerReactionStabilizationData(double rateValue, int prevState, int nextState) :
    ReactionData<DimerData>(rateValue, prevState, nextState) {}

double DimerReactionStabilizationData::rate(const DimerData &dimer) const {
    return (dimer.first->value() == this->prevState() && dimer.second->value() == this->prevState()) ?
                this->k() : 0;
}

void DimerReactionStabilizationData::doIt(DimerData *const dimer) const {
    dimer->first->setValue(this->nextState());
    dimer->second->setValue(this->nextState());
}

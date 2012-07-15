#include "dimerreactioncapture_data.h"

DimerReactionCaptureData::DimerReactionCaptureData(double rateValue, int prevState, int nextState) :
    ReactionData<DimerData>(rateValue, prevState, nextState) {}

double DimerReactionCaptureData::rate(const DimerData *dimer) const {
    return ((dimer->first->value() == this->nextState() && dimer->second->value() == this->prevState()) ||
            (dimer->first->value() == this->prevState() && dimer->second->value() == this->nextState())) ?
                this->k() : 0;
}

void DimerReactionCaptureData::doIt(DimerData *const dimer) const {
    if (dimer->first->value() == this->prevState()) {
        dimer->first->setValue(this->nextState());
    } else {
        dimer->second->setValue(this->nextState());
    }
}


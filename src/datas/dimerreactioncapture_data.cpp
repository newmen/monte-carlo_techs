#include "dimerreactioncapture_data.h"

DimerReactionCaptureData::DimerReactionCaptureData(int prevState, int nextState, long double k) :
    ReactionData<DimerData>(prevState, nextState, k) {}

long double DimerReactionCaptureData::rate(const DimerData *dimer) const {
    return ((dimer->first->value() == nextState() && dimer->second->value() == prevState()) ||
            (dimer->first->value() == prevState() && dimer->second->value() == nextState())) ?
                rateValue(dimer) : 0;
}

void DimerReactionCaptureData::doIt(DimerData *const dimer) const {
    if (dimer->first->value() == prevState()) {
        dimer->first->setValue(nextState());
    } else {
        dimer->second->setValue(nextState());
    }
}


#include "cellreaction_data.h"

CellReactionData::CellReactionData(double rateValue, int prevState, int nextState) :
    ReactionData<CellData>(rateValue, prevState, nextState) {}

double CellReactionData::rate(const CellData *site) const {
    return (site->value() == this->prevState()) ? this->k() : 0;
}

void CellReactionData::doIt(CellData *const site) const {
    site->setValue(this->nextState());
}


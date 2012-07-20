#include "cellreaction_data.h"

CellReactionData::CellReactionData(double k, int prevState, int nextState) :
    ReactionData<CellData>(k, prevState, nextState) {}

double CellReactionData::rate(const CellData *site) const {
    return (site->value() == prevState()) ? rateValue(site) : 0;
}

void CellReactionData::doIt(CellData *const site) const {
    site->setValue(nextState());
}

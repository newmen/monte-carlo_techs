#include "cellreaction_data.h"

CellReactionData::CellReactionData(int prevState, int nextState, long double k) :
    ReactionData<CellData>(prevState, nextState, k) {}

long double CellReactionData::rate(const CellData *site) const {
    return (site->value() == prevState()) ? rateValue(site) : 0;
}

void CellReactionData::doIt(CellData *const site) const {
    site->setValue(nextState());
}

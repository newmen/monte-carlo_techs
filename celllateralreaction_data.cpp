#include "celllateralreaction_data.h"
#include "lateralcell_data.h"

CellLateralReactionData::CellLateralReactionData(int prevState, int nextState, const RTReactorContext *reactor, long double k, long double Ea, long double epss[], int numOfSpecs) :
    CellReactionData(k, prevState, nextState), LateralReactionData(reactor, Ea, epss, numOfSpecs) {}

long double CellLateralReactionData::rateValue(const CellData *cell) const {
    const LateralCellData *lateralCell = static_cast<const LateralCellData *>(cell);
    return this->k() * expFactor(lateralCell);
}

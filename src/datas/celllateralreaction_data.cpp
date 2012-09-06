#include "celllateralreaction_data.h"
#include "lateralcell_data.h"

CellLateralReactionData::CellLateralReactionData(int prevState, int nextState, long double k, long double Ea, long double epss[], const RTReactorContext *reactor) :
    CellReactionData(prevState, nextState, k), LateralReactionData(reactor, Ea, epss) {}

long double CellLateralReactionData::rateValue(const CellData *cell) const {
    const LateralCellData *lateralCell = static_cast<const LateralCellData *>(cell);
    return this->k() * expFactor(lateralCell);
}

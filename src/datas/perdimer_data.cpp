#include "perdimer_data.h"
#include "percell_data.h"

PerDimerData::PerDimerData(DimerData *const dimer) : PerSiteData(dimer) {
    _perCells[0] = _perCells[1] = 0;
}

void PerDimerData::addPerCell(PerCellData *const perCell) {
    PerCellData **p = (_perCells[0] != 0) ? &_perCells[1] : &_perCells[0];
    *p = perCell;
}

//void PerDimerData::doReaction(const BaseSimulationContext *simulationContext, long double r) {
//    PerSiteData<DimerData>::doReaction(simulationContext, r);
//}

void PerDimerData::updateAroundRates(const BaseSimulationContext *simulationContext, int depth) {
    updateRates(simulationContext);
    if (depth == 0) return;

    // logical for depth = 1
    int exsDimerIndex = (first()->site()->x() != second()->site()->x()) ? 3 : 2;
    first()->updateAroundRates(simulationContext, depth);
    second()->updateAroundRates(simulationContext, depth, exsDimerIndex);
}

PerCellData *PerDimerData::first() const {
    return _perCells[0];
}

PerCellData *PerDimerData::second() const {
    return _perCells[1];
}

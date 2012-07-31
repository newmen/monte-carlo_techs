#include "perdimer_data.h"
#include "percell_data.h"

PerDimerData::PerDimerData(DimerData *const dimer) : PerSiteData(dimer) {
    _perCells[0] = _perCells[1] = 0;
}

void PerDimerData::addPerCell(PerCellData *const perCell) {
    PerCellData **p = (_perCells[0] != 0) ? &_perCells[1] : &_perCells[0];
    *p = perCell;
}

void PerDimerData::doReaction(const BaseSimulationContext *simulationContext, long double r) {
    PerSiteData<DimerData>::doReaction(simulationContext, r);
    for (PerCellData *perCell : _perCells) {
        perCell->updateRates(simulationContext, this);
    }
}

PerCellData *PerDimerData::first() const {
    return _perCells[0];
}

PerCellData *PerDimerData::second() const {
    return _perCells[1];
}

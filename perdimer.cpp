#include "perdimer.h"
#include "percell.h"

PerDimer::PerDimer(DimerData *const dimer) : PerSite(dimer) {
    _perCells[0] = _perCells[1] = 0;
}

void PerDimer::addPerCell(PerCell *const perCell) {
    PerCell **p = (_perCells[0] != 0) ? &_perCells[1] : &_perCells[0];
    *p = perCell;
}

void PerDimer::doReaction(const SimulationBaseContext *simulationContext, long double r) {
    PerSite<DimerData>::doReaction(simulationContext, r);
    for (PerCell *perCell : _perCells) {
        perCell->updateRates(simulationContext, this);
    }
}

PerCell *PerDimer::first() const {
    return _perCells[0];
}

PerCell *PerDimer::second() const {
    return _perCells[1];
}

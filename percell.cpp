#include "percell.h"
#include "perdimer.h"

PerCell::PerCell(CellData *const cell) : PerSite(cell), _numOfPerDimers(0) {}

void PerCell::addPerDimer(PerDimer *const perDimer) {
    _perDimers[_numOfPerDimers++] = perDimer;
}

void PerCell::updateRates() {
    updateRates(nullptr);
}

void PerCell::updateRates(const PerDimer *exceptPerDimer) {
    PerSite<CellData>::updateRates();
    for (PerDimer *perDimer : _perDimers) {
        if (perDimer == exceptPerDimer) continue;
        perDimer->updateRates();

        PerCell *neighbour = (perDimer->first() == this) ? perDimer->second() : perDimer->first();
        neighbour->updateLocalCommonRate();
    }
}

void PerCell::updateLocalCommonRate() {
    PerSite<CellData>::updateRates();
}

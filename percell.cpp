#include "percell.h"
#include "perdimer.h"

PerCell::PerCell(CellData *const cell) : PerSite(cell), _numOfPerDimers(0) {}

void PerCell::addPerDimer(PerDimer *const perDimer) {
    _perDimers[_numOfPerDimers++] = perDimer;
    incCommonRate(perDimer->commonRate());
}

void PerCell::updateRates() {
    updateRates(nullptr);
}

void PerCell::updateRates(const PerDimer *exceptPerDimer) {
    PerSite<CellData>::updateRates();
    for (PerDimer *perDimer : _perDimers) {
        if (perDimer != exceptPerDimer) {
            perDimer->updateRates();

            PerCell *neighbour = (perDimer->first() == this) ? perDimer->second() : perDimer->first();
            neighbour->updateLocalCommonRate();
        }
        incCommonRate(perDimer->commonRate());
    }
}

void PerCell::updateLocalCommonRate() {
    PerSite<CellData>::updateRates();
    for (PerDimer *perDimer : _perDimers) {
        incCommonRate(perDimer->commonRate());
    }
}

void PerCell::doReaction(double r) {
    if (doLocalReaction(r)) return;

    for (PerDimer *perDimer : _perDimers) {
        if (r < perDimer->commonRate()) {
            perDimer->doReaction(r);
            break;
        } else {
            r -= perDimer->commonRate();
        }
    }
}

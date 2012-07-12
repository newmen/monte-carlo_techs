#include "perdimer.h"
#include "percell.h"

PerDimer::PerDimer(DimerData *const dimer) : PerSite(dimer), _numOfPerCells(0) {}

void PerDimer::addPerCell(PerCell *const perCell) {
    _perCells[_numOfPerCells++] = perCell;
}

void PerDimer::doReaction(double r) {
    PerSite<DimerData>::doReaction(r);
    for (PerCell *perCell : _perCells) {
        perCell->updateRates(this);
    }

}

PerCell *PerDimer::first() const {
    return _perCells[0];
}

PerCell *PerDimer::second() const {
    return _perCells[1];
}

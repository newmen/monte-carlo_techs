#include <map>
#include "kineticsimulation_context.h"

KineticSimulationContext::KineticSimulationContext(AreaData *area) : SiteBasedSimulationContext(area) {
    initData();
}

KineticSimulationContext::~KineticSimulationContext() {
    for (auto p = _perCells.begin(); p != _perCells.end(); ++p) delete *p;
}

double KineticSimulationContext::doReaction() {
    double dt = 0;
    PerCell *minPerSite = findMin(&dt);

    if (dt == 0) return 0;

    doRandomReaction(minPerSite);

    return dt;
}

void KineticSimulationContext::storeCell(PerCell *const perCell) {
    _perCells.push_back(perCell);
}

PerCell *KineticSimulationContext::findMin(double *dt) const {
    PerCell *min = 0;
    for (auto p = _perCells.cbegin(); p != _perCells.cend(); ++p) {
        if ((*p)->commonRate() == 0) continue;

        double localDt = negativLogU() / (*p)->commonRate();
        if (*dt == 0 || localDt < *dt) {
            *dt = localDt;
            min = *p;
        }
    }
    return min;
}

void KineticSimulationContext::doRandomReaction(PerCell *const perCell) {
    perCell->doReaction(perCell->commonRate() * randomN01());
}

#include "percell.h"
#include "perdimer.h"

PerCell::PerCell(CellData *const cell) : PerSite(cell) {
    for (int i = 0; i < PERDIMERS_NUM; ++i) _perDimers[i] = 0;
}

void PerCell::addPerDimer(PerDimer *const perDimer) {
    int numOfPerDimers = 0;
    for (int i = 0; i < PERDIMERS_NUM; ++i) {
        if (_perDimers[i] != 0) ++numOfPerDimers;
    }

    // this scope of conditions is depend from NeighbouringRole::uniqPairs method
    // and need for resolv correct perDimer other side index in updateRates method
    auto conditionsScope = [this, &perDimer](int i0, int i1, int i2, int i3) {
        PerDimer **p = 0;
        if (site()->y() == 0 && site()->x() == 0) p = &_perDimers[i0];
        else if (site()->y() == 0 && site()->x() > 0) p = &_perDimers[i1];
        else if (site()->y() > 0 && site()->x() == 0) p = &_perDimers[i2];
        else /*if (site()->y() > 0 && site()->x() > 0)*/ p = &_perDimers[i3];
        *p = perDimer;
    };

    switch (numOfPerDimers) {
    case 0:
        conditionsScope(1, 3, 0, 0);
        break;
    case 1:
        conditionsScope(2, 1, 1, 3);
        break;
    case 2:
        conditionsScope(3, 2, 2, 1);
        break;
    case 3:
        conditionsScope(0, 0, 3, 2);
        break;
    }
}

void PerCell::updateRates(const SimulationBaseContext *simulationContext) {
    updateRates(simulationContext, nullptr);
}

void PerCell::updateRates(const SimulationBaseContext *simulationContext, const PerDimer *exceptPerDimer) {
    PerSite<CellData>::updateRates(simulationContext);
    for (int i = 0; i < PERDIMERS_NUM; ++i) {
        PerDimer *perDimer = _perDimers[i];
        if (perDimer == exceptPerDimer) continue;
        perDimer->updateRates(simulationContext);

        PerCell *neighbour = (perDimer->first() == this) ? perDimer->second() : perDimer->first();
        neighbour->updateLocalCommonRate(simulationContext, (i < 2) ? i + 2 : i - 2);
    }
}

void PerCell::updateLocalCommonRate(const SimulationBaseContext *simulationContext, int otherSideIndex) {
    PerSite<CellData>::updateRates(simulationContext);
    _perDimers[otherSideIndex]->updateRates(simulationContext);
}

#ifndef PERCELL_H
#define PERCELL_H

#include "persite.h"
#include "cell_data.h"

#define PERDIMERS_NUM 4

class PerDimer;

class PerCell : public PerSite<CellData>
{
public:
    PerCell(CellData *const cell);

    void addPerDimer(PerDimer *const perDimer);

    void updateRates(const SimulationBaseContext *simulationContext);
    virtual void updateRates(const SimulationBaseContext *simulationContext, const PerDimer *exceptPerDimer);
    virtual void updateLocalCommonRate(const SimulationBaseContext *simulationContext, int otherSideIndex);

private:
    PerDimer *_perDimers[PERDIMERS_NUM];
};

#endif // PERCELL_H

#ifndef PERCELL_DATA_H
#define PERCELL_DATA_H

#include "persite_data.h"
#include "cell_data.h"

#define PERDIMERS_NUM 4

class PerDimerData;

class PerCellData : public PerSiteData<CellData>
{
public:
    PerCellData(CellData *const cell);

    void addPerDimer(PerDimerData *const perDimer);

    void updateRates(const BaseSimulationContext *simulationContext);
    virtual void updateRates(const BaseSimulationContext *simulationContext, const PerDimerData *exceptPerDimer);
    virtual void updateLocalCommonRate(const BaseSimulationContext *simulationContext, int otherSideIndex);

private:
    PerDimerData *_perDimers[PERDIMERS_NUM];
};

#endif // PERCELL_DATA_H

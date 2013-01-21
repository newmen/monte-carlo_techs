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

    void updateAroundRates(const BaseSimulationContext *simulationContext, int depth);
    virtual void updateAroundRates(const BaseSimulationContext *simulationContext, int depth, int woDimerIndex); // optimization
    virtual void updateAroundRates(const BaseSimulationContext *simulationContext, int depth, PerDimerData *exceptDimer); // optimization

private:
    PerDimerData *_perDimers[PERDIMERS_NUM];
};

#endif // PERCELL_DATA_H

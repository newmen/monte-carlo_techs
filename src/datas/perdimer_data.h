#ifndef PERDIMER_DATA_H
#define PERDIMER_DATA_H

#include "persite_data.h"
#include "dimer_data.h"

class PerCellData;

class PerDimerData : public PerSiteData<DimerData>
{
public:
    PerDimerData(DimerData *const dimer);

    void addPerCell(PerCellData *const perCell);

//    void doReaction(const BaseSimulationContext *simulationContext, long double r);

    void updateAroundRates(const BaseSimulationContext *simulationContext, int depth);

    PerCellData *first() const;
    PerCellData *second() const;

private:
    PerCellData *_perCells[2];
};

#endif // PERDIMER_DATA_H

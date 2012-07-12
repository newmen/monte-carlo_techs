#ifndef PERCELL_H
#define PERCELL_H

#include "persite.h"
#include "cell_data.h"

class PerDimer;

class PerCell : public PerSite<CellData>
{
public:
    PerCell(CellData *const cell);

    void addPerDimer(PerDimer *const perDimer);

    void updateRates();
    virtual void updateRates(const PerDimer *exceptPerDimer);
    virtual void updateLocalCommonRate();

private:
    PerDimer *_perDimers[4];
    int _numOfPerDimers;
};

#endif // PERCELL_H

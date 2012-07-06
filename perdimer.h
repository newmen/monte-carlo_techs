#ifndef PERDIMER_H
#define PERDIMER_H

#include "persite.h"
#include "dimer_data.h"

class PerCell;

class PerDimer : public PerSite<DimerData>
{
public:
    PerDimer(DimerData *const dimer);

    void addPerCell(PerCell *const perCell);

    void doReaction(double r);

    PerCell *first() const;
    PerCell *second() const;

private:
    PerCell *_perCells[2];
    int _numOfPerCells;
};

#endif // PERDIMER_H

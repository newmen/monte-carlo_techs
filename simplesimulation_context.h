#ifndef SIMPLYSIMULATION_CONTEXT_H
#define SIMPLYSIMULATION_CONTEXT_H

#include "simulationbase_context.h"

class SimpleSimulationContext : public SimulationBaseContext
{
protected:
    SimpleSimulationContext(AreaData *area);

    virtual void clearAllEvents() = 0;

    virtual void addCellEvent(CellData *const cell, const CellReaction *const reaction) = 0;
    virtual void addDimerEvent(DimerData *const dimer, const DimerReaction *const reaction) = 0;

    void reviewAllEvents();
};

#endif // SIMPLYSIMULATION_CONTEXT_H

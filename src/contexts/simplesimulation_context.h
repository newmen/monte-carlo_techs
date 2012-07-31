#ifndef SIMPLYSIMULATION_CONTEXT_H
#define SIMPLYSIMULATION_CONTEXT_H

#include "basesimulation_context.h"

class SimpleSimulationContext : public BaseSimulationContext
{
protected:
    SimpleSimulationContext(AreaData *area, const BaseReactorContext *reactor);

    virtual void clearAllEvents() = 0;

    virtual void addCellEvent(CellData *const cell, const ReactionData<CellData> *const reaction) = 0;
    virtual void addDimerEvent(DimerData *const dimer, const ReactionData<DimerData> *const reaction) = 0;

    void reviewAllEvents();
};

#endif // SIMPLYSIMULATION_CONTEXT_H

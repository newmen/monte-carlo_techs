#ifndef OPTIMIZEDSIMPLYSIMULATION_CONTEXT_H
#define OPTIMIZEDSIMPLYSIMULATION_CONTEXT_H

#include <map>
#include <functional>
#include "basesimulation_context.h"

#define DIMERS_PER_CELL 4

class OptimizedSimpleSimulationContext : public BaseSimulationContext
{
protected:
    OptimizedSimpleSimulationContext(AreaData *area, const BaseReactorContext *reactor);
    ~OptimizedSimpleSimulationContext();

    virtual void addCellEvent(CellData *const cell, const ReactionData<CellData> *const reaction) = 0;
    virtual void addDimerEvent(DimerData *const dimer, const ReactionData<DimerData> *const reaction) = 0;

    void reviewAllEvents();

    void doAround(CellData *cell, const std::function<void (CellData *cell)> &cellLambda, const std::function<void (DimerData *cell)> &dimerLambda, int delph = 1, int woDimerIndex = -1);
    void doAround(DimerData *dimer, const std::function<void (CellData *cell)> &cellLambda, const std::function<void (DimerData *cell)> &dimerLambda);

private:
    void bindCellDimer(CellData *cell, DimerData *dimer);

private:
    std::map<CellData *, DimerData **> _cellsToDimers;
};

#endif // OPTIMIZEDSIMPLYSIMULATION_CONTEXT_H

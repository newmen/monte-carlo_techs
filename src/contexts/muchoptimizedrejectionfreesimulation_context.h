#ifndef MUCHOPTIMIZEDREJECTIONFREESIMULATION_CONTEXT_H
#define MUCHOPTIMIZEDREJECTIONFREESIMULATION_CONTEXT_H

#include "optimizedeventbasedsimulation_context.h"

class MuchOptimizedRejectionFreeSimulationContext : public OptimizedEventBasedSimulationContext
{
public:
    MuchOptimizedRejectionFreeSimulationContext(AreaData *area, const BaseReactorContext *reactor);

protected:
    BaseEventData *randomEvent() const;
};

#endif // MUCHOPTIMIZEDREJECTIONFREESIMULATION_CONTEXT_H

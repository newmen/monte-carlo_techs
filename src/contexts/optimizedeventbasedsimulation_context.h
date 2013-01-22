#ifndef OPTIMIZEDEVENTBASEDSIMULATION_CONTEXT_H
#define OPTIMIZEDEVENTBASEDSIMULATION_CONTEXT_H

#include <vector>
#include "commonoptimizedeventbasedsimulation_context.h"
#include "../datas/event_data.h"

class OptimizedEventBasedSimulationContext : public CommonOptimizedEventBasedSimulationContext
{
protected:
    OptimizedEventBasedSimulationContext(AreaData *area, const BaseReactorContext *reactor);
    ~OptimizedEventBasedSimulationContext();

    void clearAllEvents() {} // cap

    void storeEvent(BaseEventData *event);
    void recountTotalRate();

    virtual void doWhenEventAddedWithRate(long double) {}
    virtual void clearLocalVars() {}

    long double recountAround(CellData *const cell);
    long double recountAround(DimerData *const dimer);

private:
    template <class SData>
    long double recountAroundSite(SData *const site);

    template <class SData>
    long double updateEvent(EventData<SData> *event);

protected:
    std::vector<BaseEventData *> _events;
};

#endif // OPTIMIZEDEVENTBASEDSIMULATION_CONTEXT_H

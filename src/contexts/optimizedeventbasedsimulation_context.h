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
    EventInfoData doEvent(BaseEventData *event);
    void recountTotalRate();
    virtual void doWhenEventAddedWithRate(long double) {}

private:
    template <class SData>
    long double recountAround(SData *const site);

    template <class SData>
    long double updateEvent(EventData<SData> *event);

protected:
    std::vector<BaseEventData *> _events;
};

#endif // OPTIMIZEDEVENTBASEDSIMULATION_CONTEXT_H

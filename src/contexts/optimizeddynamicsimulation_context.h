#ifndef OPTIMIZEDDYNAMICSIMULATION_CONTEXT_H
#define OPTIMIZEDDYNAMICSIMULATION_CONTEXT_H

#include <map>
#include <vector>
#include "commonoptimizedeventbasedsimulation_context.h"
#include "../datas/event_data.h"

class OptimizedDynamicSimulationContext : public CommonOptimizedEventBasedSimulationContext
{
    typedef std::vector<BaseEventData *> Events;
    typedef std::pair<long double, const Events *> RatesPEventsPair;
public:
    OptimizedDynamicSimulationContext(AreaData *area, const BaseReactorContext *reactor);
    ~OptimizedDynamicSimulationContext();

protected:
    void storeEvent(BaseEventData *event);
    BaseEventData *randomEvent() const;
    EventInfoData doEvent(BaseEventData *event);
    void recountTotalRate();

private:
    void insertSearchPair(long double oneRate, const Events *events);
    void sortSearchContainer();

    template <class SData>
    long double recountAround(SData *const site);

    template <class SData>
    long double updateEvent(EventData<SData> *event);

private:
    std::map<long double, Events> _rateToEvents;
    std::map<long double, RatesPEventsPair *> _rateToSearchPair;
    std::vector<RatesPEventsPair *> _searchContainer;

    const int _sortEachStep;
    int _steps;
};

#endif // OPTIMIZEDDYNAMICSIMULATION_CONTEXT_H

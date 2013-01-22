#include "optimizedeventbasedsimulation_context.h"

OptimizedEventBasedSimulationContext::OptimizedEventBasedSimulationContext(AreaData *area, const BaseReactorContext *reactor) :
    CommonOptimizedEventBasedSimulationContext(area, reactor)
{
    reviewAllEvents();
}

OptimizedEventBasedSimulationContext::~OptimizedEventBasedSimulationContext() {
    for (auto *event : _events) delete event;
}

void OptimizedEventBasedSimulationContext::storeEvent(BaseEventData *event) {
    doWhenEventAddedWithRate(event->rate());
    _events.push_back(event);
}

void OptimizedEventBasedSimulationContext::recountTotalRate() {
    clearTotalRate();
    clearLocalVars();
    for (BaseEventData *event : _events) {
        long double rate = event->rate();
        incTotalRate(rate);
        doWhenEventAddedWithRate(rate);
    }
}

long double OptimizedEventBasedSimulationContext::recountAround(CellData *const cell) {
    return recountAroundSite(cell);
}

long double OptimizedEventBasedSimulationContext::recountAround(DimerData *const dimer) {
    return recountAroundSite(dimer);
}

template <class SData>
long double OptimizedEventBasedSimulationContext::recountAroundSite(SData *const site) {
    long double sum = 0;
    doAround(site, [this, &sum](CellData *cell) {
        this->reinitSite(cell);
        long double localSum = 0;
        for (EventData<CellData> *event : this->_cellEvents[cell]) {
            localSum += updateEvent(event);
        }
        this->_cellRates[cell] = localSum;
        sum += localSum;
    }, [this, &sum](DimerData *dimer) {
        this->reinitSite(dimer);
        long double localSum = 0;
        for (EventData<DimerData> *event : this->_dimerEvents[dimer]) {
            localSum += updateEvent(event);
        }
        this->_dimerRates[dimer] = localSum;
        sum += localSum;
    });
    return sum;
}

template <class SData>
long double OptimizedEventBasedSimulationContext::updateEvent(EventData<SData> *event) {
    event->update();
    long double newRate = event->rate();
    this->doWhenEventAddedWithRate(newRate);
    return newRate;
}

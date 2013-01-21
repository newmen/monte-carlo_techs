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

EventInfoData OptimizedEventBasedSimulationContext::doEvent(BaseEventData *event) {
    EventInfoData info = event->info(negativLogU() / totalRate());
    EventData<CellData> *cellEvent;
    EventData<DimerData> *dimerEvent;

    long double oldRate;
    if (info.cell()) {
        cellEvent = static_cast<EventData<CellData> *>(event);
        oldRate = countAround(cellEvent->site());
    } else {
        dimerEvent = static_cast<EventData<DimerData> *>(event);
        oldRate = countAround(dimerEvent->site());
    }

    event->doIt();

    long double newRate;
    if (info.cell()) {
        newRate = recountAround(cellEvent->site());
    } else {
        newRate = recountAround(dimerEvent->site());
    }

    incTotalRate(newRate - oldRate);

    return info;
}

void OptimizedEventBasedSimulationContext::recountTotalRate() {
    clearTotalRate();
    for (BaseEventData *event : _events) {
        incTotalRate(event->rate());
    }
}

template <class SData>
long double OptimizedEventBasedSimulationContext::recountAround(SData *const site) {
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

#ifndef REJECTIONSIMULATION_CONTEXT_H
#define REJECTIONSIMULATION_CONTEXT_H

#include "basesimulation_context.h"
#include "../datas/baseevent_data.h"

template <class EBSimulationContext>
class RejectionSimulationContext : public EBSimulationContext
{
public:
    RejectionSimulationContext(AreaData *area, const BaseReactorContext *reactor);

protected:
    BaseEventData *randomEvent() const;
    void clearAllEvents();

    void doWhenEventAddedWithRate(long double rate);
    void clearLocalVars();

private:
    long double _maxRate;
};

template <class EBSimulationContext>
RejectionSimulationContext<EBSimulationContext>::RejectionSimulationContext(AreaData *area, const BaseReactorContext *reactor) :
    EBSimulationContext(area, reactor), _maxRate(0) {}

template <class EBSimulationContext>
BaseEventData *RejectionSimulationContext<EBSimulationContext>::randomEvent() const {
    long double r;
    int n;
    BaseEventData *selectedEvent;
    do {
        r = this->randomN01() * this->_events.size();
        n = int(r);
        selectedEvent = this->_events[n];
    } while (n - r + 1 >= selectedEvent->rate() / _maxRate);
    return selectedEvent;
}

template <class EBSimulationContext>
void RejectionSimulationContext<EBSimulationContext>::clearAllEvents() {
    EBSimulationContext::clearAllEvents();
    clearLocalVars();
}

template <class EBSimulationContext>
void RejectionSimulationContext<EBSimulationContext>::doWhenEventAddedWithRate(long double rate) {
    if (rate > _maxRate) _maxRate = rate;
}

template <class EBSimulationContext>
void RejectionSimulationContext<EBSimulationContext>::clearLocalVars() {
    _maxRate = 0;
}

#endif // REJECTIONSIMULATION_CONTEXT_H

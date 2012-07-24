#include "rejectionsimulation_context.h"

RejectionSimulationContext::RejectionSimulationContext(AreaData *area, const ReactorBaseContext *reactor) :
    EventBasedSimulationContext(area, reactor), _maxRate(0) {}

BaseEvent *RejectionSimulationContext::randomEvent() const {
    long double r;
    int n;
    BaseEvent *selectedEvent;
    do {
        r = randomN01() * _events.size();
        n = int(r);
        selectedEvent = _events[n];
    } while (n - r + 1 >= selectedEvent->rate() / _maxRate);
    return selectedEvent;
}

void RejectionSimulationContext::clearAllEvents() {
    EventBasedSimulationContext::clearAllEvents();
    _maxRate = 0;
}

void RejectionSimulationContext::doWhenEventAddedWithRate(long double rate) {
    if (rate > _maxRate) _maxRate = rate;
}


#include "rejectionfreesimulation_context.h"

RejectionFreeSimulationContext::RejectionFreeSimulationContext(AreaData *area, const ReactorBaseContext *reactor) :
    EventBasedSimulationContext(area, reactor) {}

BaseEvent *RejectionFreeSimulationContext::randomEvent() const {
    long double r = randomN01() * totalRate();
    long double accRate = 0;
    for (auto p = _events.begin(); p != _events.end(); ++p) {
        accRate += (*p)->rate();
        if (r < accRate) return *p;
    };
    return 0;
}

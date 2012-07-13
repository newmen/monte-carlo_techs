#include "rejectionfreesimulation_context.h"

RejectionFreeSimulationContext::RejectionFreeSimulationContext(AreaData *area, const ReactorBaseData *reactor) :
    EventBasedSimulationContext(area, reactor) {}

BaseEvent *RejectionFreeSimulationContext::randomEvent() const {
    double r = randomN01() * totalRate();
    double accRate = 0;
    for (auto p = _events.begin(); p != _events.end(); ++p) {
        accRate += (*p)->rate();
        if (r < accRate) return *p;
    };
    return 0;
}

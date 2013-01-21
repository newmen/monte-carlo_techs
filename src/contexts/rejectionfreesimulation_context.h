#ifndef REJECTIONFREESIMULATION_CONTEXT_H
#define REJECTIONFREESIMULATION_CONTEXT_H

#include "basesimulation_context.h"

template <class EBSimulationContext>
class RejectionFreeSimulationContext : public EBSimulationContext
{
public:
    RejectionFreeSimulationContext(AreaData *area, const BaseReactorContext *reactor);

protected:
    BaseEventData *randomEvent() const;

};

template <class EBSimulationContext>
RejectionFreeSimulationContext<EBSimulationContext>::RejectionFreeSimulationContext(AreaData *area, const BaseReactorContext *reactor) :
    EBSimulationContext(area, reactor) {}

template <class EBSimulationContext>
BaseEventData *RejectionFreeSimulationContext<EBSimulationContext>::randomEvent() const {
    long double r = this->randomN01() * this->totalRate();
    long double accRate = 0;
    for (auto p = this->_events.begin(); p != this->_events.end(); ++p) {
        accRate += (*p)->rate();
        if (r < accRate) return *p;
    };
    return 0;
}

#endif // REJECTIONFREESIMULATION_CONTEXT_H

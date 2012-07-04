#ifndef REJECTIONSIMULATION_CONTEXT_H
#define REJECTIONSIMULATION_CONTEXT_H

#include "eventbasedsimulation_context.h"

class RejectionSimulationContext : public EventBasedSimulationContext
{
public:
    RejectionSimulationContext(AreaData *area);

protected:
    BaseEventData *randomEvent() const;
    void clearAllEvents();
    void doWhenEventAddedWithRate(double rate);

private:
    double _maxRate;
};

#endif // REJECTIONSIMULATION_CONTEXT_H

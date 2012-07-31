#ifndef REJECTIONSIMULATION_CONTEXT_H
#define REJECTIONSIMULATION_CONTEXT_H

#include "eventbasedsimulation_context.h"

class RejectionSimulationContext : public EventBasedSimulationContext
{
public:
    RejectionSimulationContext(AreaData *area, const BaseReactorContext *reactor);

protected:
    BaseEventData *randomEvent() const;
    void clearAllEvents();
    void doWhenEventAddedWithRate(long double rate);

private:
    long double _maxRate;
};

#endif // REJECTIONSIMULATION_CONTEXT_H

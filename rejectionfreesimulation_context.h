#ifndef REJECTIONFREESIMULATION_CONTEXT_H
#define REJECTIONFREESIMULATION_CONTEXT_H

#include "eventbasedsimulation_context.h"

class RejectionFreeSimulationContext : public EventBasedSimulationContext
{
public:
    RejectionFreeSimulationContext(AreaData *area);

protected:
    BaseEvent *randomEvent() const;

};

#endif // REJECTIONFREESIMULATION_CONTEXT_H

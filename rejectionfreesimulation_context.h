#ifndef REJECTIONFREESIMULATION_CONTEXT_H
#define REJECTIONFREESIMULATION_CONTEXT_H

//#include <list>
#include <vector>
#include "simulationbase_context.h"
#include "event_data.h"

class RejectionFreeSimulationContext : public SimulationBaseContext
{
public:
    RejectionFreeSimulationContext(AreaData *area);

    float doReaction();

private:
    void reviewAllEvents();

//    std::list<EventData> _events;
    std::vector<EventData> _events;
    float _totalRate;
};

#endif // REJECTIONFREESIMULATION_CONTEXT_H

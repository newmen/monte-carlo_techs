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

    double doReaction();

private:
    void reviewAllEvents();

private:
//    std::list<EventData> _events;
    std::vector<EventData> _events;
    double _totalRate;
};

#endif // REJECTIONFREESIMULATION_CONTEXT_H

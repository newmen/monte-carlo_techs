#ifndef REJECTIONSIMULATION_CONTEXT_H
#define REJECTIONSIMULATION_CONTEXT_H

#include <vector>
#include "simulationbase_context.h"
#include "event_data.h"

class RejectionSimulationContext : public SimulationBaseContext
{
public:
    RejectionSimulationContext(AreaData *area);

    float doReaction();

private:
    void reviewAllEvents();
    int randomEventIndex() const;
    void doEvent(int index);

    std::vector<EventData> _events;
    float _totalRate, _maxRate;
};

#endif // REJECTIONSIMULATION_CONTEXT_H

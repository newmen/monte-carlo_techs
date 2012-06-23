#ifndef DYNAMICSIMULATION_CONTEXT_H
#define DYNAMICSIMULATION_CONTEXT_H

#include <vector>
#include "simulationbase_context.h"

class DynamicSimulationContext : public SimulationBaseContext
{
public:
    DynamicSimulationContext(AreaData *area);

    float doReaction();

private:
    void reviewAllEvents();

private:
    std::vector<SiteData> _sites[REACTIONS_NUM];
    float _rates[REACTIONS_NUM];
    float _totalRate;
};

#endif // DYNAMICSIMULATION_CONTEXT_H

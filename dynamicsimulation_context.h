#ifndef DYNAMICSIMULATION_CONTEXT_H
#define DYNAMICSIMULATION_CONTEXT_H

#include <vector>
#include "simulationbase_context.h"

class DynamicSimulationContext : public SimulationBaseContext
{
public:
    DynamicSimulationContext(AreaData *area);

    double doReaction();

private:
    void reviewAllEvents();

private:
    std::vector<SiteData> _sites[REACTIONS_NUM];
    double _rates[REACTIONS_NUM];
    double _totalRate;
};

#endif // DYNAMICSIMULATION_CONTEXT_H

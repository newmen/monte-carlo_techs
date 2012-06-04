#ifndef REJECTIONFREESIMULATION_CONTEXT_H
#define REJECTIONFREESIMULATION_CONTEXT_H

#include <vector>
#include "simulationbase_context.h"

class RejectionFreeSimulationContext : public SimulationBaseContext
{
public:
    RejectionFreeSimulationContext(AreaData *area);

    float doReaction();

private:
    void reviewAllEvents();

    std::vector<SiteData> _sites[REACTIONS_NUM];
    int _numberOfReactions[REACTIONS_NUM];
};

#endif // REJECTIONFREESIMULATION_CONTEXT_H

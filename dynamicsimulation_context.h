#ifndef DYNAMICSIMULATION_CONTEXT_H
#define DYNAMICSIMULATION_CONTEXT_H

#include <list>
#include "simulationbase_context.h"
#include "site_data.h"

class DynamicSimulationContext : public SimulationBaseContext
{
public:
    DynamicSimulationContext(AreaData *area);
    ~DynamicSimulationContext();

    float doReaction();

private:
    void collectSites();
    int proportionalReactionRandomIndex(float *totalRate) const;
    SiteData *randomSite(int reactionIndex);

    int _numberOfReactions[REACTIONS_NUM];
    std::list<SiteData> _sites[REACTIONS_NUM];
};

#endif // DYNAMICSIMULATION_CONTEXT_H

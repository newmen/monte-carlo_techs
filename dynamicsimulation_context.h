#ifndef DYNAMICSIMULATION_CONTEXT_H
#define DYNAMICSIMULATION_CONTEXT_H

#include <vector>
#include "simulationbase_context.h"

class DynamicSimulationContext : public SimulationBaseContext
{
    typedef std::vector<SiteData> SitesList;

public:
    DynamicSimulationContext(AreaData *area);
    ~DynamicSimulationContext();

    double doReaction();

private:
    void reviewAllEvents();

private:
    SitesList *_sites;
    double *_rates;
    double _totalRate;
};

#endif // DYNAMICSIMULATION_CONTEXT_H

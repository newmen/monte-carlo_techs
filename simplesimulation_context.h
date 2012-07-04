#ifndef SIMPLYSIMULATION_CONTEXT_H
#define SIMPLYSIMULATION_CONTEXT_H

#include "simulationbase_context.h"

class SimpleSimulationContext : public SimulationBaseContext
{
protected:
    SimpleSimulationContext(AreaData *area);

    virtual void clearAllEvents() = 0;

    virtual void addSiteEvent(const SharedSite &site, const SiteReaction *const reaction) = 0;
    virtual void addDimerEvent(const SharedDimer &dimer, const DimerReaction *const reaction) = 0;

    void reviewAllEvents();
    void estimateEachReactionForSite(const SharedSite &site);
    void estimateEachReactionForDimer(const SharedDimer &dimer);
};

#endif // SIMPLYSIMULATION_CONTEXT_H

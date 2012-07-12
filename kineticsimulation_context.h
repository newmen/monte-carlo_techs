#ifndef KINETICSIMULATION_CONTEXT_H
#define KINETICSIMULATION_CONTEXT_H

#include "sitebasedsimulation_context.h"
#include "percell.h"
#include "perdimer.h"

class KineticSimulationContext : public SiteBasedSimulationContext<PerCell, PerDimer>
{
public:
    KineticSimulationContext(AreaData *area);
    ~KineticSimulationContext();

    double doReaction();

protected:
    void storeCell(PerCell *const perCell);
    void storeDimer(PerDimer *const perDimer);

private:
    IPerSite *findMin(double *dt) const;
    void doRandomReaction(IPerSite *const perSite);

private:
    std::vector<IPerSite *> _perSites;
};

#endif // KINETICSIMULATION_CONTEXT_H

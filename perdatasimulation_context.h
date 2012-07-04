#ifndef PERDATASIMULATION_CONTEXT_H
#define PERDATASIMULATION_CONTEXT_H

#include <functional>
#include <map>
#include <vector>
#include <set>
#include "simulationbase_context.h"
#include "persiteordimer_data.h"

class PerDataSimulationContext : public SimulationBaseContext
{
protected:
    typedef PerSiteOrDimerData<SiteData> PerSite;
    typedef PerSiteOrDimerData<DimerData> PerDimer;
    typedef std::set<PerDimer *> PerDimerCache;

protected:
    PerDataSimulationContext(AreaData *area);

    void estimateEachReactionForSite(const SharedSite &site);
    void estimateEachReactionForDimer(const SharedDimer &dimer);

    virtual PerSite *createData(const SharedSite &site) const = 0;
    virtual PerDimer *createData(const SharedDimer &dimer) const = 0;

    virtual void store(PerSite *perSite) = 0;
    virtual void store(PerDimer *perDimer) = 0;

    void updateNeighbours(PerSite *perSite);
    void updateNeighbours(PerDimer *perDimer);

private:
    std::function<void (const SharedSite &)> updateNeighboursRatesLambda() const;

    void addRates(PerSite *perSite) const;
    void addRates(PerDimer *perDimer) const;

    void updateAssociatedDimersRates(const int *cell, PerDimerCache *perDimerCache = 0);

private:
    std::map<const int *, PerSite *> _cellsToPerSites;
    std::map<const int *, std::vector<PerDimer *> > _cellsToPerDimers;
};

#endif // PERDATASIMULATION_CONTEXT_H

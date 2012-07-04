#ifndef DYNAMICSIMULATION_CONTEXT_H
#define DYNAMICSIMULATION_CONTEXT_H

#include <map>
#include <vector>
#include "simplesimulation_context.h"
#include "site_data.h"
#include "dimer_data.h"

class DynamicSimulationContext : public SimpleSimulationContext
{
    typedef std::map<const SiteReaction *const, std::vector<SharedSite> > SitesMap;
    typedef std::map<const DimerReaction *const, std::vector<SharedDimer> > DimersMap;
    typedef std::map<const SiteReaction *const, double> RatesOnSitesMap;
    typedef std::map<const DimerReaction *const, double> RatesOnDimersMap;

public:
    DynamicSimulationContext(AreaData *area);
//    ~DynamicSimulationContext();

    double doReaction();

protected:
    void clearAllEvents();

    void addSiteEvent(const SharedSite &site, const SiteReaction *const reaction);
    void addDimerEvent(const SharedDimer &dimer, const DimerReaction *const reaction);

private:
    template <class SDData>
    void addEvent(std::map<const IReactingRole<SDData> *const, std::vector<std::shared_ptr<SDData> > > *dataContainer, std::map<const IReactingRole<SDData> *const, double> *rates, const std::shared_ptr<SDData> &siteOrDimer, const IReactingRole<SDData> *const reaction);

    template <class SDData>
    const IReactingRole<SDData> *findReaction(double *r, double *max, const std::map<const IReactingRole<SDData> *const, double> &ratesMap) const;

    template <class SDData>
    void clearEvents(std::map<const IReactingRole<SDData> *const, std::vector<std::shared_ptr<SDData> > > *dataContainer, std::map<const IReactingRole<SDData> *const, double> *rates);

private:
    SitesMap _sites;
    DimersMap _dimers;

    RatesOnSitesMap _ratesOnSites;
    RatesOnDimersMap _ratesOnDimers;

    double _totalRate;
};

#endif // DYNAMICSIMULATION_CONTEXT_H

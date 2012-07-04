#ifndef SIMULATIONBASE_CONTEXT_H
#define SIMULATIONBASE_CONTEXT_H

#include <functional>
#include <vector>
#include "area_data.h"
#include "site_data.h"
#include "dimer_data.h"
#include "ireacting_role.h"

class SimulationBaseContext
{
public:
    SimulationBaseContext(AreaData *area);
    virtual ~SimulationBaseContext();

    virtual double doReaction() = 0;

protected:
    typedef IReactingRole<SiteData> SiteReaction;
    typedef IReactingRole<DimerData> DimerReaction;

    int siteReactionsNum() const;
    int dimerReactionsNum() const;

    virtual void reviewAllEvents();
    virtual void estimateEachReactionForSite(const SharedSite &site) = 0;
    virtual void estimateEachReactionForDimer(const SharedDimer &dimer) = 0;

    void eachSiteReaction(std::function<void (const SiteReaction *const)> lambda) const;
    void eachSiteNeighbour(const SiteData &site, std::function<void (const SharedSite &)> lambda) const;
    void eachDimerReaction(std::function<void (const DimerReaction *const)> lambda) const;
    void eachDimerNeighbour(const DimerData &dimer, std::function<void (const SharedSite &)> lambda) const;

    double randomN01() const;
    double negativLogU() const;

private:
    AreaData *_area;
    std::vector<const SiteReaction *> _siteReactions;
    std::vector<const DimerReaction *> _dimerReactions;
};

#endif // SIMULATIONBASE_CONTEXT_H

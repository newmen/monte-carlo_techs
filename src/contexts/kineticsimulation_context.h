#ifndef KINETICSIMULATION_CONTEXT_H
#define KINETICSIMULATION_CONTEXT_H

#include "sitebasedsimulation_context.h"
#include "../datas/percell_data.h"
#include "../datas/perdimer_data.h"

class KineticSimulationContext : public SiteBasedSimulationContext<PerCellData, PerDimerData>
{
public:
    KineticSimulationContext(AreaData *area, const BaseReactorContext *reactor);
    ~KineticSimulationContext();

    EventInfoData doReaction();

protected:
    void storeCell(PerCellData *const perCell);
    void storeDimer(PerDimerData *const perDimer);

private:
    BasePerSiteData *findMin(long double *dt) const;
    void doRandomReaction(BasePerSiteData *const perSite);

private:
    std::vector<BasePerSiteData *> _perSites;
};

#endif // KINETICSIMULATION_CONTEXT_H

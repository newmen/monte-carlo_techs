#include <map>
#include "kineticsimulation_context.h"

KineticSimulationContext::KineticSimulationContext(AreaData *area, const BaseReactorContext *reactor) :
    SiteBasedSimulationContext(area, reactor)
{
    initData();
}

KineticSimulationContext::~KineticSimulationContext() {
    for (auto p = _perSites.begin(); p != _perSites.end(); ++p) delete *p;
}

EventInfoData KineticSimulationContext::doReaction() {
    long double dt = -1.0;
    BasePerSiteData *minPerSite = findMin(&dt);

    if (dt == -1.0) return EventInfoData(-1.0);

    doRandomReaction(minPerSite);

    EventInfoData ei(dt);
    PerCellData *perCell = dynamic_cast<PerCellData *>(minPerSite);
    if (perCell) ei.set(perCell->site());
    else ei.set(dynamic_cast<PerDimerData *>(minPerSite)->site());

    return ei;
}

void KineticSimulationContext::storeCell(PerCellData *const perCell) {
    _perSites.push_back(perCell);
}

void KineticSimulationContext::storeDimer(PerDimerData *const perDimer) {
    _perSites.push_back(perDimer);
}

BasePerSiteData *KineticSimulationContext::findMin(long double *dt) const {
    BasePerSiteData *min = 0;
    for (auto p = _perSites.cbegin(); p != _perSites.cend(); ++p) {
        if ((*p)->commonRate() == 0.0) continue;

        long double localDt = negativLogU() / (*p)->commonRate();
        if (*dt == -1.0 || localDt < *dt) {
            *dt = localDt;
            min = *p;
        }
    }
    return min;
}

void KineticSimulationContext::doRandomReaction(BasePerSiteData *const perSite) {
    perSite->doReaction(this, perSite->commonRate() * randomN01());
}

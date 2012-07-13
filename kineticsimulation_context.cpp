#include <map>
#include "kineticsimulation_context.h"

KineticSimulationContext::KineticSimulationContext(AreaData *area, const ReactorBaseData *reactor) :
    SiteBasedSimulationContext(area, reactor)
{
    initData();
}

KineticSimulationContext::~KineticSimulationContext() {
    for (auto p = _perSites.begin(); p != _perSites.end(); ++p) delete *p;
}

double KineticSimulationContext::doReaction() {
    double dt = 0;
    IPerSite *minPerSite = findMin(&dt);

    if (dt == 0) return 0;

    doRandomReaction(minPerSite);

    return dt;
}

void KineticSimulationContext::storeCell(PerCell *const perCell) {
    _perSites.push_back(perCell);
}

void KineticSimulationContext::storeDimer(PerDimer *const perDimer) {
    _perSites.push_back(perDimer);
}

IPerSite *KineticSimulationContext::findMin(double *dt) const {
    IPerSite *min = 0;
    for (auto p = _perSites.cbegin(); p != _perSites.cend(); ++p) {
        if ((*p)->commonRate() == 0) continue;

        double localDt = negativLogU() / (*p)->commonRate();
        if (*dt == 0 || localDt < *dt) {
            *dt = localDt;
            min = *p;
        }
    }
    return min;
}

void KineticSimulationContext::doRandomReaction(IPerSite *const perSite) {
    perSite->doReaction(perSite->commonRate() * randomN01());
}

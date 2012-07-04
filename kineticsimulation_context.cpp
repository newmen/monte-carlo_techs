#include "kineticsimulation_context.h"

KineticSimulationContext::KineticSimulationContext(AreaData *area) : PerDataSimulationContext(area) {
    reviewAllEvents();
}

KineticSimulationContext::~KineticSimulationContext() {
    for (auto p = _perSites.begin(); p != _perSites.end(); ++p) delete *p;
    for (auto p = _perDimers.begin(); p != _perDimers.end(); ++p) delete *p;
}

double KineticSimulationContext::doReaction() {
    double dt = 0;
    PerSite *minPerSite = findMin(&dt, _perSites);
    PerDimer *minPerDimer = findMin(&dt, _perDimers);

    if (dt == 0) return 0;

    if (!minPerDimer) doRandomReaction(minPerSite);
    else doRandomReaction(minPerDimer);

    return dt;
}

PerDataSimulationContext::PerSite *KineticSimulationContext::createData(const SharedSite &site) const {
    return new PerSite(site);
}

PerDataSimulationContext::PerDimer *KineticSimulationContext::createData(const SharedDimer &dimer) const {
    return new PerDimer(dimer);
}

void KineticSimulationContext::store(PerSite *site) {
    _perSites.push_back(site);
}

void KineticSimulationContext::store(PerDimer *dimer) {
    _perDimers.push_back(dimer);
}

template <class SDData>
PerSiteOrDimerData<SDData> *KineticSimulationContext::findMin(double *dt, const std::vector<PerSiteOrDimerData<SDData> *> &pers) const {
    PerSiteOrDimerData<SDData> *min = 0;
    for (auto p = pers.begin(); p != pers.end(); ++p) {
        if ((*p)->commonRate() > 0) {
            double localDt = negativLogU() / (*p)->commonRate();
            if (*dt == 0 || localDt < *dt) {
                *dt = localDt;
                min = *p;
            }
        }
    }
    return min;
}

template <class PerData>
void KineticSimulationContext::doRandomReaction(PerData *perData) {
    perData->doReaction(perData->commonRate() * randomN01());
    perData->updateRates();
    updateNeighbours(perData);
}

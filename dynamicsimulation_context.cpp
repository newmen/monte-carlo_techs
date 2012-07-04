#include "dynamicsimulation_context.h"

DynamicSimulationContext::DynamicSimulationContext(AreaData *area) :
    SimpleSimulationContext(area), _totalRate(0) {}

//DynamicSimulationContext::~DynamicSimulationContext() {}

double DynamicSimulationContext::doReaction() {
    reviewAllEvents();
    if (_totalRate == 0) return 0;

    double max = 0;
    double r = randomN01() * _totalRate;
    auto indexLambda = [&r, &max](unsigned int size) -> int {
        return size * r / max;
    };

    const SiteReaction *siteReaction = findReaction(&r, &max, _ratesOnSites);
    if (siteReaction) {
        auto &sites = _sites[siteReaction];
        siteReaction->doIt(sites[indexLambda(sites.size())].get());
    } else {
        const DimerReaction *dimerReaction = findReaction(&r, &max, _ratesOnDimers);
        auto &dimers = _dimers[dimerReaction];
        dimerReaction->doIt(dimers[indexLambda(dimers.size())].get());
    }

    return negativLogU() / _totalRate;
}

void DynamicSimulationContext::clearAllEvents() {
    clearEvents(&_sites, &_ratesOnSites);
    clearEvents(&_dimers, &_ratesOnDimers);
    _totalRate = 0;
}

void DynamicSimulationContext::addSiteEvent(const SharedSite &site, const SiteReaction *const reaction) {
    addEvent(&_sites, &_ratesOnSites, site, reaction);
}

void DynamicSimulationContext::addDimerEvent(const SharedDimer &dimer, const DimerReaction *const reaction) {
    addEvent(&_dimers, &_ratesOnDimers, dimer, reaction);
}

template <class SDData>
void DynamicSimulationContext::addEvent(std::map<const IReactingRole<SDData> *const, std::vector<std::shared_ptr<SDData> > > *dataContainer,
                                        std::map<const IReactingRole<SDData> *const, double> *rates,
                                        const std::shared_ptr<SDData> &siteOrDimer,
                                        const IReactingRole<SDData> *const reaction)
{
    double rate = reaction->rate(*siteOrDimer);
    if (rate > 0) {
        (*dataContainer)[reaction].push_back(siteOrDimer);
        (*rates)[reaction] += rate;
        _totalRate += rate;
    }
}

template <class SDData>
const IReactingRole<SDData> *DynamicSimulationContext::findReaction(double *r, double *max, const std::map<const IReactingRole<SDData> *const, double> &ratesMap) const
{
    const IReactingRole<SDData> *reaction = 0;
    for (auto p = ratesMap.cbegin(); p != ratesMap.cend(); ++p) {
        *max = p->second;
        if (*r < p->second) {
            reaction = p->first;
            break;
        } else {
            *r -= p->second;
        }
    }
    return reaction;
}

template <class SDData>
void DynamicSimulationContext::clearEvents(std::map<const IReactingRole<SDData> *const, std::vector<std::shared_ptr<SDData> > > *dataContainer,
                                           std::map<const IReactingRole<SDData> *const, double> *rates) {
    for (auto p = dataContainer->begin(); p != dataContainer->end(); ++p) p->second.clear();
    for (auto p = rates->begin(); p != rates->end(); ++p) p->second = 0;
}

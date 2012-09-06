#ifndef PERSITE_DATA_H
#define PERSITE_DATA_H

#include <map>
#include "basepersite_data.h"
#include "reaction_data.h"

template <class SData>
class PerSiteData : public BasePerSiteData
{
    typedef std::map<const ReactionData<SData> *, long double> RatesMap;

public:
    virtual ~PerSiteData() {}

    void addReaction(const ReactionData<SData> *const reaction);

    long double commonRate() const;
    void doReaction(const BaseSimulationContext *simulationContext, long double r);

    // must be public!
    virtual void updateRates(const BaseSimulationContext *simulationContext);
    virtual void updateAroundRates(const BaseSimulationContext *simulationContext, int depth) = 0;

    SData *site() const;

protected:
    PerSiteData(SData *const site);

private:
    SData *_site;
    RatesMap _rates;
    long double _commonRate;
};

template <class SData>
PerSiteData<SData>::PerSiteData(SData *const site) : _site(site), _commonRate(0) {}

template <class SData>
void PerSiteData<SData>::addReaction(const ReactionData<SData> *const reaction) {
    long double rate = reaction->rate(_site);
    _rates[reaction] = rate;
    _commonRate += rate;
}

template <class SData>
long double PerSiteData<SData>::commonRate() const {
    return _commonRate;
}

template <class SData>
void PerSiteData<SData>::updateRates(const BaseSimulationContext *simulationContext) {
    simulationContext->reinitSite(_site);
    _commonRate = 0;
    for (auto p = _rates.begin(); p != _rates.end(); ++p) {
        long double rate = p->first->rate(_site);
        p->second = rate;
        _commonRate += rate;
    }
}

template <class SData>
SData *PerSiteData<SData>::site() const {
    return _site;
}

template <class SData>
void PerSiteData<SData>::doReaction(const BaseSimulationContext *simulationContext, long double r) {
    for (auto p = _rates.begin(); p != _rates.end(); ++p) {
        if (r < p->second) {
            p->first->doIt(_site);
            break;
        } else {
            r -= p->second;
        }
    }
    updateAroundRates(simulationContext, 1);
}

#endif // PERSITE_DATA_H

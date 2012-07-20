#ifndef PERSITE_H
#define PERSITE_H

#include <map>
#include "ipersite.h"
#include "reaction_data.h"

template <class SData>
class PerSite : public IPerSite
{
    typedef std::map<const ReactionData<SData> *, double> RatesMap;

public:
    virtual ~PerSite() {}

    void addReaction(const ReactionData<SData> *const reaction);

    double commonRate() const;
    void doReaction(const SimulationBaseContext *simulationContext, double r);

    virtual void updateRates(const SimulationBaseContext *simulationContext);

    SData *site() const;

protected:
    PerSite(SData *const site);

private:
    SData *_site;
    RatesMap _rates;
    double _commonRate;
};

template <class SData>
PerSite<SData>::PerSite(SData *const site) : _site(site), _commonRate(0) {}

template <class SData>
void PerSite<SData>::addReaction(const ReactionData<SData> *const reaction) {
    double rate = reaction->rate(_site);
    _rates[reaction] = rate;
    _commonRate += rate;
}

template <class SData>
double PerSite<SData>::commonRate() const {
    return _commonRate;
}

template <class SData>
void PerSite<SData>::updateRates(const SimulationBaseContext *simulationContext) {
    simulationContext->reinitSite(_site);
    _commonRate = 0;
    for (auto p = _rates.begin(); p != _rates.end(); ++p) {
        double rate = p->first->rate(_site);
        p->second = rate;
        _commonRate += rate;
    }
}

template <class SData>
SData *PerSite<SData>::site() const {
    return _site;
}

template <class SData>
void PerSite<SData>::doReaction(const SimulationBaseContext *simulationContext, double r) {
    for (auto p = _rates.begin(); p != _rates.end(); ++p) {
        if (r < p->second) {
            p->first->doIt(_site);
            break;
        } else {
            r -= p->second;
        }
    }
    updateRates(simulationContext);
}

#endif // PERSITE_H
#ifndef PERSITE_H
#define PERSITE_H

#include <map>
#include "ireacting_role.h"

template <class SData>
class PerSite
{
    typedef std::map<const IReactingRole<SData> *, double> RatesMap;

public:
    virtual ~PerSite() {}

    void addReaction(const IReactingRole<SData> *const reaction);
    double commonRate() const;
    virtual void updateRates();

    virtual void doReaction(double r) = 0;

protected:
    PerSite(SData *const site);

    void incCommonRate(double rate);
    bool doLocalReaction(double &r);

private:
    SData *_site;
    RatesMap _rates;
    double _commonRate;
};

template <class SData>
PerSite<SData>::PerSite(SData *const site) : _site(site), _commonRate(0) {}

template <class SData>
void PerSite<SData>::addReaction(const IReactingRole<SData> *const reaction) {
    double rate = reaction->rate(*_site);
    _rates[reaction] = rate;
    _commonRate += rate;
}

template <class SData>
double PerSite<SData>::commonRate() const {
    return _commonRate;
}

template <class SData>
void PerSite<SData>::updateRates() {
    _commonRate = 0;
    for (auto p = _rates.begin(); p != _rates.end(); ++p) {
        double rate = p->first->rate(*_site);
        p->second = rate;
        _commonRate += rate;
    }
}

template <class SData>
void PerSite<SData>::incCommonRate(double rate) {
    _commonRate += rate;
}

template <class SData>
bool PerSite<SData>::doLocalReaction(double &r) {
    for (auto p = _rates.begin(); p != _rates.end(); ++p) {
        if (r < p->second) {
            p->first->doIt(_site);
            updateRates();
            return true;
        } else {
            r -= p->second;
        }
    }
    return false;
}

#endif // PERSITE_H

#ifndef PERSITEORDIMER_DATA_H
#define PERSITEORDIMER_DATA_H

#include <map>
#include <memory>
#include "ireacting_role.h"

template <class SDData>
class PerSiteOrDimerData
{
    typedef std::map<const IReactingRole<SDData> *const, double> RatesMap;

public:
    PerSiteOrDimerData(const std::shared_ptr<SDData> &siteOrDimer) :
        _siteOrDimer(siteOrDimer), _commonRate(0) {}
    virtual ~PerSiteOrDimerData() {}

    virtual void updateRates();
    void addRate(const IReactingRole<SDData> *const reaction);

    void doReaction(double r);
    double commonRate() const { return _commonRate; }
    const SDData &siteOrDimer() const { return *_siteOrDimer; }

private:
    const IReactingRole<SDData> *selectReaction(double r) const;

private:
    std::shared_ptr<SDData> _siteOrDimer;
    RatesMap _rates;
    double _commonRate;
};

template <class SDData>
void PerSiteOrDimerData<SDData>::updateRates() {
    _commonRate = 0;
    for (auto p = _rates.begin(); p != _rates.end(); ++p) {
        double rate = p->first->rate(*_siteOrDimer);
        p->second = rate;
        _commonRate += rate;
    }
}

template <class SDData>
void PerSiteOrDimerData<SDData>::addRate(const IReactingRole<SDData> *const reaction) {
    double rate = reaction->rate(*_siteOrDimer);
    _rates[reaction] = rate;
    _commonRate += rate;
}

template <class SDData>
void PerSiteOrDimerData<SDData>::doReaction(double r) {
    const IReactingRole<SDData> *const reaction = selectReaction(r);
    reaction->doIt(_siteOrDimer.get());
}

template <class SDData>
const IReactingRole<SDData> *PerSiteOrDimerData<SDData>::selectReaction(double r) const {
    for (auto p = _rates.cbegin(); p != _rates.cend(); ++p) {
        if (r < p->second) return p->first;
        else r -= p->second;
    }
    return 0;
}

#endif // PERSITEORDIMER_DATA_H

#include "eventbasedsimulation_context.h"
#include "event_data.h"

EventBasedSimulationContext::EventBasedSimulationContext(AreaData *area) :
    SimpleSimulationContext(area), _totalRate(0) {}

double EventBasedSimulationContext::doReaction() {
    reviewAllEvents();
    if (_totalRate == 0) return 0;
    randomEvent()->doIt();

    return negativLogU() / _totalRate;
}

void EventBasedSimulationContext::clearAllEvents() {
    for (auto p = _events.begin(); p != _events.end(); ++p) delete *p;
    _events.clear();
    _totalRate = 0;
}

void EventBasedSimulationContext::addSiteEvent(const SharedSite &site, const SiteReaction *const reaction) {
    addEvent(site, reaction);
}

void EventBasedSimulationContext::addDimerEvent(const SharedDimer &dimer, const DimerReaction *const reaction) {
    addEvent(dimer, reaction);
}

template <class SDData>
void EventBasedSimulationContext::addEvent(const std::shared_ptr<SDData> &siteOrDimer, const IReactingRole<SDData> *const reaction)
{
    double rate = reaction->rate(*siteOrDimer);
    doWhenEventAddedWithRate(rate);
    if (rate > 0) {
        _totalRate += rate;
        _events.push_back(new EventData<SDData>(siteOrDimer, reaction, rate));
    }
}

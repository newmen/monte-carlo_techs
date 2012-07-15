#include "eventbasedsimulation_context.h"
#include "event.h"

EventBasedSimulationContext::EventBasedSimulationContext(AreaData *area, const ReactorBaseData *reactor) :
    SimpleSimulationContext(area, reactor), _totalRate(0) {}

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

void EventBasedSimulationContext::addCellEvent(CellData *const cell, const ReactionData<CellData> *const reaction) {
    addEvent(cell, reaction);
}

void EventBasedSimulationContext::addDimerEvent(DimerData *const dimer, const ReactionData<DimerData> *const reaction) {
    addEvent(dimer, reaction);
}

template <class SData>
void EventBasedSimulationContext::addEvent(SData *const site, const ReactionData<SData> *const reaction) {
    double rate = reaction->rate(site);
    doWhenEventAddedWithRate(rate);
    if (rate > 0) {
        _totalRate += rate;
        _events.push_back(new Event<SData>(site, reaction, rate));
    }
}

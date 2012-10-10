#include "eventbasedsimulation_context.h"
#include "../datas/event_data.h"

EventBasedSimulationContext::EventBasedSimulationContext(AreaData *area, const BaseReactorContext *reactor) :
    SimpleSimulationContext(area, reactor), _totalRate(0) {}

EventInfoData EventBasedSimulationContext::doReaction() {
    reviewAllEvents();

    if (_totalRate == 0.0) return EventInfoData(-1.0);

    BaseEventData *event = randomEvent();
    event->doIt();

    return event->info(negativLogU() / _totalRate);
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
    long double rate = reaction->rate(site);
    doWhenEventAddedWithRate(rate);
    if (rate > 0.0) {
        _totalRate += rate;
        _events.push_back(new EventData<SData>(site, reaction, rate));
    }
}

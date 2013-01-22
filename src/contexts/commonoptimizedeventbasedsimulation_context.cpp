#include <iostream>
#include "commonoptimizedeventbasedsimulation_context.h"

CommonOptimizedEventBasedSimulationContext::CommonOptimizedEventBasedSimulationContext(AreaData *area, const BaseReactorContext *reactor) :
    OptimizedSimpleSimulationContext(area, reactor), _totalRate(0) {}

EventInfoData CommonOptimizedEventBasedSimulationContext::doReaction() {
    bool isRealyOver = false;
    while (true) {
        if (_totalRate <= 0.0) {
            if (isRealyOver) break;
            else {
                std::cerr << "ONE TIME! -> recountTotalRate()" << std::endl;
                isRealyOver = true;
                recountTotalRate();
                continue;
            }
        }

        BaseEventData *event = randomEvent();
        if (event == 0) {
            std::cerr << "Event not found! -> recountTotalRate()" << std::endl;
            isRealyOver = true;
            recountTotalRate();
            continue;
        }
        return doEvent(event);
    }
    return EventInfoData(-1.0);
}

void CommonOptimizedEventBasedSimulationContext::addCellEvent(CellData *const cell, const ReactionData<CellData> *const reaction) {
    addEvent(cell, reaction);
}

void CommonOptimizedEventBasedSimulationContext::addDimerEvent(DimerData *const dimer, const ReactionData<DimerData> *const reaction) {
    addEvent(dimer, reaction);
}

EventInfoData CommonOptimizedEventBasedSimulationContext::doEvent(BaseEventData *event) {
    EventInfoData info = event->info(negativLogU() / totalRate());
    EventData<CellData> *cellEvent;
    EventData<DimerData> *dimerEvent;

    long double oldRate;
    if (info.cell()) {
        cellEvent = static_cast<EventData<CellData> *>(event);
        oldRate = countAround(cellEvent->site());
    } else {
        dimerEvent = static_cast<EventData<DimerData> *>(event);
        oldRate = countAround(dimerEvent->site());
    }

    event->doIt();

    long double newRate;
    if (info.cell()) {
        newRate = recountAround(cellEvent->site());
    } else {
        newRate = recountAround(dimerEvent->site());
    }

    _totalRate += newRate - oldRate;

    return info;
}

template <class SData>
void CommonOptimizedEventBasedSimulationContext::addEvent(SData *const site, const ReactionData<SData> *const reaction) {
    long double rate = reaction->rate(site);
    EventData<SData> *event = new EventData<SData>(site, reaction, rate);
    assignEventToSite(site, event);
    _totalRate += rate;

    storeEvent(event);
}

template <>
void CommonOptimizedEventBasedSimulationContext::assignEventToSite<CellData>(CellData *const cell, EventData<CellData> *const event) {
    if (_cellRates.find(cell) == _cellRates.cend()) _cellRates[cell] = 0;
    _cellRates[cell] += event->rate();
    _cellEvents[cell].push_back(event);
}

template <>
void CommonOptimizedEventBasedSimulationContext::assignEventToSite<DimerData>(DimerData *const dimer, EventData<DimerData> *const event) {
    if (_dimerRates.find(dimer) == _dimerRates.cend()) _dimerRates[dimer] = 0;
    _dimerRates[dimer] += event->rate();
    _dimerEvents[dimer].push_back(event);
}

long double CommonOptimizedEventBasedSimulationContext::countAround(CellData *const cell) {
    return countAroundSite(cell);
}

long double CommonOptimizedEventBasedSimulationContext::countAround(DimerData *const dimer) {
    return countAroundSite(dimer);
}

template <class SData>
long double CommonOptimizedEventBasedSimulationContext::countAroundSite(SData *const site) {
    long double sum = 0;
    doAround(site, [this, &sum](CellData *cell) {
        sum += this->_cellRates[cell];
    }, [this, &sum](DimerData *dimer) {
        sum += this->_dimerRates[dimer];
    });
    return sum;
}

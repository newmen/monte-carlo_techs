#include <algorithm>
#include "optimizeddynamicsimulation_context.h"

OptimizedDynamicSimulationContext::OptimizedDynamicSimulationContext(AreaData *area, const BaseReactorContext *reactor) :
    CommonOptimizedEventBasedSimulationContext(area, reactor), _sortEachStep(area->size()), _steps(0)
{
    reviewAllEvents();
    for (auto p = _rateToEvents.cbegin(); p != _rateToEvents.cend(); ++p) {
        insertSearchPair(p->first, &p->second);
    }
    sortSearchContainer();
}

OptimizedDynamicSimulationContext::~OptimizedDynamicSimulationContext() {
    for (auto pSearchPair = _searchContainer.begin(); pSearchPair != _searchContainer.end(); ++pSearchPair) {
        delete *pSearchPair;
    }

    for (auto pRateEvent = _rateToEvents.begin(); pRateEvent != _rateToEvents.end(); ++pRateEvent) {
        for (auto pEvent = pRateEvent->second.begin(); pEvent != pRateEvent->second.end(); ++pEvent) {
            delete *pEvent;
        }
    }
}

void OptimizedDynamicSimulationContext::storeEvent(BaseEventData *event) {
    if (event->rate() > 0) {
        _rateToEvents[event->rate()].push_back(event);
    }
}

BaseEventData *OptimizedDynamicSimulationContext::randomEvent() const {
    long double r = randomN01() * totalRate();
    for (auto p = _searchContainer.cbegin(); p != _searchContainer.cend(); ++p) {
        if (r < (*p)->first) {
            int innerIndex = (*p)->second->size() * r / (*p)->first;
            return (*(*p)->second)[innerIndex];
        } else {
            r -= (*p)->first;
        }
    }
    return 0;
}

EventInfoData OptimizedDynamicSimulationContext::doEvent(BaseEventData *event) {
    EventInfoData info = CommonOptimizedEventBasedSimulationContext::doEvent(event);

    if (++_steps > _sortEachStep) {
        sortSearchContainer();
        _steps = 0;
    }

    return info;
}

void OptimizedDynamicSimulationContext::recountTotalRate() {
    clearTotalRate();
    for (auto p = _searchContainer.cbegin(); p != _searchContainer.cend(); ++p) {
        incTotalRate((*p)->first);
    }
}

void OptimizedDynamicSimulationContext::insertSearchPair(long double oneRate, const Events *events) {
    RatesPEventsPair *searchPair = new RatesPEventsPair(oneRate * events->size(), events);
    _searchContainer.push_back(searchPair);
    _rateToSearchPair[oneRate] = searchPair;
}

void OptimizedDynamicSimulationContext::sortSearchContainer() {
    std::sort(_searchContainer.begin(), _searchContainer.end(), [](const RatesPEventsPair *p1, const RatesPEventsPair *p2) {
        return p1->first > p2->first;
    });
}

long double OptimizedDynamicSimulationContext::recountAround(CellData *const cell) {
    return recountAroundSite(cell);
}

long double OptimizedDynamicSimulationContext::recountAround(DimerData *const dimer) {
    return recountAroundSite(dimer);
}

template <class SData>
long double OptimizedDynamicSimulationContext::recountAroundSite(SData *const site) {
    long double sum = 0;
    doAround(site, [this, &sum](CellData *cell) {
        this->reinitSite(cell);
        long double localSum = 0;
        for (EventData<CellData> *event : this->_cellEvents[cell]) {
            localSum += updateEvent(event);
        }
        this->_cellRates[cell] = localSum;
        sum += localSum;
    }, [this, &sum](DimerData *dimer) { // копипаста лямбд
        this->reinitSite(dimer);
        long double localSum = 0;
        for (EventData<DimerData> *event : this->_dimerEvents[dimer]) {
            localSum += updateEvent(event);
        }
        this->_dimerRates[dimer] = localSum;
        sum += localSum;
    });
    return sum;
}

template <class SData>
long double OptimizedDynamicSimulationContext::updateEvent(EventData<SData> *event) {
    long double oldRate = event->rate();
    event->update();
    long double newRate = event->rate();

    if (oldRate != newRate) {
        if (oldRate > 0) {
            Events &fromVector = this->_rateToEvents[oldRate];
            Events::iterator p = std::find(fromVector.begin(), fromVector.end(), event);
            fromVector.erase(p);
            this->_rateToSearchPair[oldRate]->first -= oldRate;
        }
        if (newRate > 0) {
            this->_rateToEvents[newRate].push_back(event);
            if (this->_rateToSearchPair.find(newRate) == this->_rateToSearchPair.cend()) {
                insertSearchPair(newRate, &this->_rateToEvents[newRate]);
            } else {
                this->_rateToSearchPair[newRate]->first += newRate;
            }
        }
    }
    return newRate;
}

#include "dynamicsimulation_context.h"

DynamicSimulationContext::DynamicSimulationContext(AreaData *area, const ReactorBaseContext *reactor) :
    SimpleSimulationContext(area, reactor), _totalRate(0) {}

//DynamicSimulationContext::~DynamicSimulationContext() {}

EventInfoData DynamicSimulationContext::doReaction() {
    reviewAllEvents();
    if (_totalRate == 0) return EventInfoData(0);

    long double max = 0;
    long double r = randomN01() * _totalRate;
    auto indexLambda = [&r, &max](unsigned int size) -> int {
        return size * r / max;
    };

    EventInfoData ei(negativLogU() / _totalRate);
    const ReactionData<CellData> *cellReaction = findReaction(&r, &max, _ratesOnSites);
    if (cellReaction) {
        auto &cells = _cells[cellReaction];
        CellData *cell = cells[indexLambda(cells.size())];
        cellReaction->doIt(cell);
        ei.set(cell);
    } else {
        const ReactionData<DimerData> *dimerReaction = findReaction(&r, &max, _ratesOnDimers);
        auto &dimers = _dimers[dimerReaction];
        DimerData *dimer = dimers[indexLambda(dimers.size())];
        dimerReaction->doIt(dimer);
        ei.set(dimer);
    }

    return ei;
}

void DynamicSimulationContext::clearAllEvents() {
    clearEvents(&_cells, &_ratesOnSites);
    clearEvents(&_dimers, &_ratesOnDimers);
    _totalRate = 0;
}

void DynamicSimulationContext::addCellEvent(CellData *const cell, const ReactionData<CellData> *const reaction) {
    addEvent(&_cells, &_ratesOnSites, cell, reaction);
}

void DynamicSimulationContext::addDimerEvent(DimerData *const dimer, const ReactionData<DimerData> *const reaction) {
    addEvent(&_dimers, &_ratesOnDimers, dimer, reaction);
}

template <class SData>
void DynamicSimulationContext::addEvent(std::map<const ReactionData<SData> *const, std::vector<SData *> > *dataContainer,
                                        std::map<const ReactionData<SData> *const, long double> *rates,
                                        SData *const site,
                                        const ReactionData<SData> *const reaction)
{
    long double rate = reaction->rate(site);
    if (rate > 0) {
        (*dataContainer)[reaction].push_back(site);
        (*rates)[reaction] += rate;
        _totalRate += rate;
    }
}

template <class SData>
const ReactionData<SData> *DynamicSimulationContext::findReaction(long double *r, long double *max,
                                                                  const std::map<const ReactionData<SData> *const, long double> &ratesMap) const
{
    const ReactionData<SData> *reaction = 0;
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

template <class SData>
void DynamicSimulationContext::clearEvents(std::map<const ReactionData<SData> *const, std::vector<SData *> > *dataContainer,
                                           std::map<const ReactionData<SData> *const, long double> *rates) {
    for (auto p = dataContainer->begin(); p != dataContainer->end(); ++p) p->second.clear();
    for (auto p = rates->begin(); p != rates->end(); ++p) p->second = 0;
}

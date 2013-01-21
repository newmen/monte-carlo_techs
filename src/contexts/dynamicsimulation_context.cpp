#include "dynamicsimulation_context.h"

DynamicSimulationContext::DynamicSimulationContext(AreaData *area, const BaseReactorContext *reactor) :
    SimpleSimulationContext(area, reactor), _totalRate(0) {}

//DynamicSimulationContext::~DynamicSimulationContext() {}

EventInfoData DynamicSimulationContext::doReaction() {
    reviewAllEvents();
    if (_totalRate == 0.0) return EventInfoData(-1.0);

    EventInfoData ei(negativLogU() / _totalRate);

    long double r = randomN01() * _totalRate;
    CellData *cell = findAndDoReaction(&r, _cells);
    if (cell) {
        ei.set(cell);
    } else {
        DimerData *dimer = findAndDoReaction(&r, _dimers);
        ei.set(dimer);
    }

    return ei;
}

void DynamicSimulationContext::clearAllEvents() {
    _cells.clear();
    _dimers.clear();
    _totalRate = 0;
}

void DynamicSimulationContext::addCellEvent(CellData *cell, const ReactionData<CellData> *reaction) {
    addEvent(&_cells, cell, reaction);
}

void DynamicSimulationContext::addDimerEvent(DimerData *dimer, const ReactionData<DimerData> *reaction) {
    addEvent(&_dimers, dimer, reaction);
}

template <class SData>
void DynamicSimulationContext::addEvent(std::map<long double, std::vector<std::pair<SData *, const ReactionData<SData> *> > > *sitesMap, SData *site, const ReactionData<SData> * reaction) {
    long double rate = reaction->rate(site);
    if (rate > 0) {
        (*sitesMap)[rate].push_back(std::pair<SData *const, const ReactionData<SData> *const>(site, reaction));
        _totalRate += rate;
    }
}

template <class SData>
SData *DynamicSimulationContext::findAndDoReaction(long double *r, const std::map<long double, std::vector<std::pair<SData *, const ReactionData<SData> *> > > &sitesMap) const
{
    SData *site = 0;
    const ReactionData<SData> *reaction = 0;
    for (auto p = sitesMap.cbegin(); p != sitesMap.cend(); ++p) {
        long double commonRate = p->first * p->second.size();
        if (*r < commonRate) {
            int index = (int)(*r / p->first);
            site = p->second[index].first;
            reaction = p->second[index].second;
            reaction->doIt(site);
            break;
        } else {
            *r -= commonRate;
        }
    }
    return site;
}

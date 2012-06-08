#include <algorithm>
#include "invertedlistsimulation_context.h"

InvertedListSimulationContext::InvertedListSimulationContext(AreaData *area) : SimulationBaseContext(area) {
    throughArea([this](int *cell, int **neighbours) {
        SiteData *site = new SiteData(cell, neighbours);
        analizeSite(site, cell);

        _cellsToSites[cell] = site;
    });
}

InvertedListSimulationContext::~InvertedListSimulationContext() {
    for (auto p = _ratesToEvents.cbegin(); p != _ratesToEvents.cend(); ++p) {
        for (Event *event : p->second) delete event;
    }

    for (auto p = _cellsToSites.cbegin(); p != _cellsToSites.cend(); ++p) {
        delete p->second;
    }
}

float InvertedListSimulationContext::doReaction() {
    auto sumOfRates = [](const std::map<float, EventsContainer>::const_iterator &p) {
        return p->first * p->second.size();
    };

    float totalRate = 0;
    for (auto p = _ratesToEvents.cbegin(); p != _ratesToEvents.cend(); ++p) {
        totalRate += sumOfRates(p);
    }

    if (totalRate == 0) return 0;

    float r = randomN01() * totalRate;
    float rate, currRateLimit;
    for (auto p = _ratesToEvents.cbegin(); p != _ratesToEvents.cend(); ++p) {
        currRateLimit = sumOfRates(p);
        if (r < currRateLimit) {
            rate = p->first;
            break;
        } else {
            r -= currRateLimit;
        }
    }

    int n = _ratesToEvents[rate].size() * r / currRateLimit;
    doEvent(rate, n);

    return negativLogU() / totalRate;
}

void InvertedListSimulationContext::analizeSite(SiteData *site, const int *cell) {
    for (int i = 0; i < REACTIONS_NUM; ++i) {
        IReactingRole *currReaction = reaction(i);
        int num = currReaction->couldBe(*site);
        if (num == 0) continue;

        float rate = num * currReaction->rate();
        Event *event = new Event(site, cell, i, num);
        _ratesToEvents[rate].push_back(event);
        _cellsToEvents[cell].push_back(event);
    }
}

void InvertedListSimulationContext::doEvent(float rate, int eventIndex) {
    auto currEventIt = _ratesToEvents[rate].begin();
    advance(currEventIt, eventIndex);

    reaction((*currEventIt)->_reactionIndex)->doIt((*currEventIt)->_site);

    removeOldData((*currEventIt)->_cell);
    addNewData((*currEventIt)->_cell);
}

void InvertedListSimulationContext::removeEventsByCell(const int *cell) {
    for (const auto &event : _cellsToEvents[cell]) {
        float eventRate = event->_numOfReactions * reaction(event->_reactionIndex)->rate();
        auto &rateEvents = _ratesToEvents[eventRate];
        rateEvents.erase(find(rateEvents.begin(), rateEvents.end(), event));

        delete event;
    }

    _cellsToEvents[cell].clear();
}

void InvertedListSimulationContext::removeOldData(const int *cell, int depth) {
    std::set<const int *> cache;
    recursiveHandle([this, &cell]() {
        removeEventsByCell(cell);
    }, &cache, cell, depth);
}

void InvertedListSimulationContext::addNewData(const int *cell, int depth) {
    std::set<const int *> cache;
    recursiveHandle([this, &cell]() {
        analizeSite(_cellsToSites[cell], cell);
    }, &cache, cell, depth);
}

void InvertedListSimulationContext::recursiveHandle(std::function<void ()> targetLambda,
                                                    std::set<const int *> *cache, const int *cell, int depth)
{
    if (cache->find(cell) != cache->end()) return;
    cache->insert(cell);

    targetLambda();
    if (depth == 0) return;

    _cellsToSites[cell]->neighboursIterator([this, &targetLambda, &cache, &depth](int *neighbourCell) {
        recursiveHandle(targetLambda, cache, neighbourCell, depth - 1);
    });
}

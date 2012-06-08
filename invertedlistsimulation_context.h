#ifndef INVERTEDLISTSIMULATION_CONTEXT_H
#define INVERTEDLISTSIMULATION_CONTEXT_H

#include <map>
#include <list>
#include <set>
#include "simulationbase_context.h"

class InvertedListSimulationContext : public SimulationBaseContext
{
public:
    InvertedListSimulationContext(AreaData *area);
    ~InvertedListSimulationContext();

    float doReaction();

private:
    void analizeSite(SiteData *site, const int *cell);
    void doEvent(float rate, int eventIndex);
    void removeEventsByCell(const int *cell);
    void removeOldData(const int *cell, int depth = 2);
    void addNewData(const int *cell, int depth = 2);
    void recursiveHandle(std::function<void ()> targetLambda, std::set<const int *> *cache, const int *cell, int depth);

    struct Event {
        SiteData *_site;
        const int *_cell;
        int _reactionIndex;
        int _numOfReactions;

        Event(SiteData *site, const int *cell, int reactionIndex, int numOfReactions) :
            _site(site), _cell(cell), _reactionIndex(reactionIndex), _numOfReactions(numOfReactions) {}
    };

    typedef std::list<Event *> EventsContainer;

    std::map<float, EventsContainer> _ratesToEvents;
    std::map<const int *, EventsContainer> _cellsToEvents;
    std::map<const int *, SiteData *> _cellsToSites;
};

#endif // INVERTEDLISTSIMULATION_CONTEXT_H

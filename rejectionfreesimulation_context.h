#ifndef REJECTIONFREESIMULATION_CONTEXT_H
#define REJECTIONFREESIMULATION_CONTEXT_H

//#include <list>
#include <vector>
#include <memory>
#include "simulationbase_context.h"

class RejectionFreeSimulationContext : public SimulationBaseContext
{
public:
    RejectionFreeSimulationContext(AreaData *area);

    float doReaction();

private:
    void reviewAllEvents();

    struct Event {
        std::shared_ptr<SiteData> _site;
        int _reactionIndex;
        float _rate;

        Event(const std::shared_ptr<SiteData> &site, int reactionIndex, float rate) :
            _site(site), _reactionIndex(reactionIndex), _rate(rate) {}
    };

//    std::list<Event> _events;
    std::vector<Event> _events;
};

#endif // REJECTIONFREESIMULATION_CONTEXT_H

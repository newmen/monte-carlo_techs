#ifndef REJECTIONSIMULATION_CONTEXT_H
#define REJECTIONSIMULATION_CONTEXT_H

#include <memory>
#include <vector>
#include "simulationbase_context.h"

class RejectionSimulationContext : public SimulationBaseContext
{
public:
    RejectionSimulationContext(AreaData *area);

    float doReaction();

private:
    struct SiteReactionRate {
        std::shared_ptr<SiteData> _site;
        int _reactionIndex;
        float _rate;

        SiteReactionRate(const std::shared_ptr<SiteData> &site, int reactionIndex, float rate) :
            _site(site), _reactionIndex(reactionIndex), _rate(rate) {}
    };

    void reviewAllEvents();
    int randomEventIndex() const;
    void doEvent(int index);

    std::vector<SiteReactionRate> _perSiteReact;
    float _totalRate, _maxRate;
};

#endif // REJECTIONSIMULATION_CONTEXT_H

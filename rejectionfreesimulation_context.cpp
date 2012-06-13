#include "rejectionfreesimulation_context.h"

RejectionFreeSimulationContext::RejectionFreeSimulationContext(AreaData *area) :
    SimulationBaseContext(area) {}

float RejectionFreeSimulationContext::doReaction() {
    reviewAllEvents();

    float totalRate = 0;
    for (auto p = _events.cbegin(); p != _events.cend(); ++p) {
        totalRate += p->_rate;
    }

    if (totalRate == 0) return 0;

    float r = randomN01() * totalRate;
    float accRate = 0;
    for (auto p = _events.cbegin(); p != _events.cend(); ++p) {
        accRate += p->_rate;
        if (r < accRate) {
            reaction(p->_reactionIndex)->doIt(p->_site.get());
            break;
        }
    }

    return negativLogU() / totalRate;
}

void RejectionFreeSimulationContext::reviewAllEvents() {
    _events.clear();

    throughArea([this](int *cell, int **neighbours) {
        std::shared_ptr<SiteData> site(new SiteData(cell, neighbours));
        for (int i = 0; i < REACTIONS_NUM; ++i) {
            int reactionsNum = reaction(i)->couldBe(*site);
            if (reactionsNum > 0) _events.push_back(Event(site, i, reactionsNum * reaction(i)->rate()));
        }
    });
}

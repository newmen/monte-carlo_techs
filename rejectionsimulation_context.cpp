#include <cmath>
#include "rejectionsimulation_context.h"

RejectionSimulationContext::RejectionSimulationContext(AreaData *area) :
    SimulationBaseContext(area), _totalRate(0), _maxRate(0) {}

double RejectionSimulationContext::doReaction() {
    reviewAllEvents();
    if (_totalRate == 0) return 0;
    doEvent(randomEventIndex());

    return negativLogU() / _totalRate;
}

void RejectionSimulationContext::reviewAllEvents() {
    _totalRate = 0;
    _maxRate = 0;
    _events.clear();
    throughArea([this](int *cell, int **neighbours) {
        std::shared_ptr<SiteData> site(new SiteData(cell, neighbours));
        for (int i = 0; i < REACTIONS_NUM; ++i) {
            IReactingRole *const currentReaction = reaction(i);
            double rate = currentReaction->couldBe(*site) * currentReaction->rate();
            if (rate == 0) continue;
            if (rate > _maxRate) _maxRate = rate;

            _totalRate += rate;
            _events.push_back(EventData(site, currentReaction, rate));
        }
    });
}

int RejectionSimulationContext::randomEventIndex() const {
    double r;
    int n;
    do {
        r = randomN01() * _events.size();
        n = int(r);
    } while (n - r + 1 >= _events[n].rate() / _maxRate);
    return n;
}

void RejectionSimulationContext::doEvent(int index) {
    EventData &event = _events[index];
    event.reaction()->doIt(event.site());
}

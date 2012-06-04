#include <cmath>
#include "rejectionsimulation_context.h"

RejectionSimulationContext::RejectionSimulationContext(AreaData *area) : SimulationBaseContext(area) {
}

float RejectionSimulationContext::doReaction() {
    reviewAllEvents();
    if (_totalRate == 0) return 0;
    doEvent(randomEventIndex());

    float u = 0;
    while (u == 0) u = randomN01();

    return -log(u) / _totalRate;
}

void RejectionSimulationContext::reviewAllEvents() {
    _totalRate = 0;
    _maxRate = 0;
    _perSiteReact.clear();
    throughArea([this](int *cell, int **neighbours) {
        std::shared_ptr<SiteData> site(new SiteData(cell, neighbours));
        for (int i = 0; i < REACTIONS_NUM; ++i) {
            float rate = reaction(i)->couldBe(*site) * reaction(i)->rate();
            if (rate == 0) continue;

            _totalRate += rate;
            if (rate > _maxRate) _maxRate = rate;
            _perSiteReact.push_back(SiteReactionRate(site, i, rate));
        }
    });
}

int RejectionSimulationContext::randomEventIndex() const {
    float r;
    int n;
    do {
        r = randomN01() * _perSiteReact.size();
        n = int(r);
    } while (n - r + 1 >= _perSiteReact[n]._rate / _maxRate);
    return n;
}

void RejectionSimulationContext::doEvent(int index) {
    SiteReactionRate &srr = _perSiteReact[index];
    reaction(srr._reactionIndex)->doIt(srr._site.get());
}

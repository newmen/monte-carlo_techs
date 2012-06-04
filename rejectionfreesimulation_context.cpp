#include "rejectionfreesimulation_context.h"

RejectionFreeSimulationContext::RejectionFreeSimulationContext(AreaData *area) :
    SimulationBaseContext(area) {}

float RejectionFreeSimulationContext::doReaction() {
    reviewAllEvents();

    float rates[REACTIONS_NUM];
    float totalRate = 0;
    for (int i = 0; i < REACTIONS_NUM; ++i) {
        rates[i] = _numberOfReactions[i] * reaction(i)->rate();
        totalRate += rates[i];
    }

    if (totalRate == 0) return 0;

    for (int i = 1; i < REACTIONS_NUM; ++i) {
        rates[i] += rates[i - 1];
    }

    int n = REACTIONS_NUM - 1;
    float r = randomN01() * totalRate;
    for (int i = 0; i < REACTIONS_NUM - 1; ++i) {
        if (r < rates[i]) {
            n = i;
            break;
        }
    }

    float min = (n == 0) ? 0 : rates[n - 1];
    float max = rates[n];
    int siteIndex = _sites[n].size() * (r - min) / (max - min);

    reaction(n)->doIt(&_sites[n][siteIndex]);
    return negativLogU() / totalRate;
}

void RejectionFreeSimulationContext::reviewAllEvents() {
    for (int i = 0; i < REACTIONS_NUM; ++i) {
        _numberOfReactions[i] = 0;
        _sites[i].clear();
    }

    throughArea([this](int *cell, int **neighbours) {
        SiteData site(cell, neighbours);
        for (int i = 0; i < REACTIONS_NUM; ++i) {
            int reactionsNum = reaction(i)->couldBe(site);
            if (reactionsNum > 0) {
                _numberOfReactions[i] += reactionsNum;
                _sites[i].push_back(site);
            }
        }
    });
}

#include "dynamicsimulation_context.h"

DynamicSimulationContext::DynamicSimulationContext(AreaData *area) :
    SimulationBaseContext(area), _totalRate(0) {}

float DynamicSimulationContext::doReaction() {
    reviewAllEvents();

    if (_totalRate == 0) return 0;

    for (int i = 1; i < REACTIONS_NUM; ++i) {
        _rates[i] += _rates[i - 1];
    }

    int n = REACTIONS_NUM - 1;
    float r = randomN01() * _totalRate;
    for (int i = 0; i < REACTIONS_NUM - 1; ++i) {
        if (r < _rates[i]) {
            n = i;
            break;
        }
    }

    float min = (n == 0) ? 0 : _rates[n - 1];
    float max = _rates[n];
    int siteIndex = _sites[n].size() * (r - min) / (max - min);

    reaction(n)->doIt(&_sites[n][siteIndex]);
    return negativLogU() / _totalRate;
}

void DynamicSimulationContext::reviewAllEvents() {
    _totalRate = 0;
    for (int i = 0; i < REACTIONS_NUM; ++i) {
        _rates[i] = 0;
        _sites[i].clear();
    }

    throughArea([this](int *cell, int **neighbours) {
        SiteData site(cell, neighbours);
        for (int i = 0; i < REACTIONS_NUM; ++i) {
            int reactionsNum = reaction(i)->couldBe(site);
            if (reactionsNum > 0) {
                float currentRate = reactionsNum * reaction(i)->rate();
                _rates[i] += currentRate;
                _totalRate += currentRate;
                _sites[i].push_back(site);
            }
        }
    });
}

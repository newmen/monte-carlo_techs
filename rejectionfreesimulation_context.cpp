#include "rejectionfreesimulation_context.h"

RejectionFreeSimulationContext::RejectionFreeSimulationContext(AreaData *area) :
    SimulationBaseContext(area), _totalRate(0) {}

double RejectionFreeSimulationContext::doReaction() {
    reviewAllEvents();

    if (_totalRate == 0) return 0;

    double r = randomN01() * _totalRate;
    double accRate = 0;
    for (auto p = _events.cbegin(); p != _events.cend(); ++p) {
        accRate += p->rate();
        if (r < accRate) {
            p->reaction()->doIt(p->site());
            break;
        }
    }

    return negativLogU() / _totalRate;
}

void RejectionFreeSimulationContext::reviewAllEvents() {
    _totalRate = 0;
    _events.clear();

    throughArea([this](int *cell, int **neighbours) {
        std::shared_ptr<SiteData> site(new SiteData(cell, neighbours));
        this->eachReaction([this, &site](IReactingRole *const currentReaction) {
            int reactionsNum = currentReaction->couldBe(*site);
            if (reactionsNum > 0) {
                double rate = reactionsNum * currentReaction->rate();
                _totalRate += rate;
                _events.push_back(EventData(site, currentReaction, rate));
            }
        });
    });
}

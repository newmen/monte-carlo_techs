#include "muchoptimizedrejectionfreesimulation_context.h"

MuchOptimizedRejectionFreeSimulationContext::MuchOptimizedRejectionFreeSimulationContext(AreaData *area, const BaseReactorContext *reactor) : OptimizedEventBasedSimulationContext(area, reactor) {}

BaseEventData *MuchOptimizedRejectionFreeSimulationContext::randomEvent() const {
    long double r = randomN01() * totalRate();
    long double accRate = 0;

    for (auto pRate = _dimerRates.cbegin(); pRate != _dimerRates.cend(); ++pRate) {
        accRate += pRate->second;
        if (r < accRate) {
            accRate -= pRate->second;
            auto &events = _dimerEvents.find(pRate->first)->second;
            for (auto pEvent = events.cbegin(); pEvent != events.cend(); ++pEvent) {
                accRate += (*pEvent)->rate();
                if (r < accRate) return *pEvent;
            }
        }
    }

    for (auto pRate = _cellRates.cbegin(); pRate != _cellRates.cend(); ++pRate) {
        accRate += pRate->second;
        if (r < accRate) {
            accRate -= pRate->second;
            auto &events = _cellEvents.find(pRate->first)->second;
            for (auto pEvent = events.cbegin(); pEvent != events.cend(); ++pEvent) {
                accRate += (*pEvent)->rate();
                if (r < accRate) return *pEvent;
            }
        }
    }

    return 0;
}

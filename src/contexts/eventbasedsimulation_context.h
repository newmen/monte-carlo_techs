#ifndef EVENTBASEDSIMULATION_CONTEXT_H
#define EVENTBASEDSIMULATION_CONTEXT_H

#include <vector>
#include "simplesimulation_context.h"
#include "../datas/baseevent_data.h"

class EventBasedSimulationContext : public SimpleSimulationContext
{
public:
    EventInfoData doReaction();

protected:
    EventBasedSimulationContext(AreaData *area, const BaseReactorContext *reactor);

    long double totalRate() const { return _totalRate; }

    void clearAllEvents();
    void addCellEvent(CellData *const cell, const ReactionData<CellData> *const reaction);
    void addDimerEvent(DimerData *const dimer, const ReactionData<DimerData> *const reation);

    virtual BaseEventData *randomEvent() const = 0;
    virtual void doWhenEventAddedWithRate(long double) {}

private:
    template <class SData>
    void addEvent(SData *const site, const ReactionData<SData> *const reaction);

protected:
    std::vector<BaseEventData *> _events;

private:
    long double _totalRate;
};

#endif // EVENTBASEDSIMULATION_CONTEXT_H

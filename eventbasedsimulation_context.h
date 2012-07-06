#ifndef EVENTBASEDSIMULATION_CONTEXT_H
#define EVENTBASEDSIMULATION_CONTEXT_H

#include <vector>
#include "simplesimulation_context.h"
#include "baseevent.h"

class EventBasedSimulationContext : public SimpleSimulationContext
{
public:
    double doReaction();

protected:
    EventBasedSimulationContext(AreaData *area);

    double totalRate() const { return _totalRate; }

    void clearAllEvents();
    void addCellEvent(CellData *const cell, const CellReaction *const reaction);
    void addDimerEvent(DimerData *const dimer, const DimerReaction *const reation);

    virtual BaseEvent *randomEvent() const = 0;
    virtual void doWhenEventAddedWithRate(double) {}

private:
    template <class SData>
    void addEvent(SData *const site, const IReactingRole<SData> *const reaction);

protected:
    std::vector<BaseEvent *> _events;

private:
    double _totalRate;
};

#endif // EVENTBASEDSIMULATION_CONTEXT_H

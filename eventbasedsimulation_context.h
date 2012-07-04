#ifndef EVENTBASEDSIMULATION_CONTEXT_H
#define EVENTBASEDSIMULATION_CONTEXT_H

#include <vector>
#include "simplesimulation_context.h"
#include "baseevent_data.h"

class EventBasedSimulationContext : public SimpleSimulationContext
{
public:
    double doReaction();

protected:
    EventBasedSimulationContext(AreaData *area);

    double totalRate() const { return _totalRate; }

    void clearAllEvents();
    void addSiteEvent(const SharedSite &site, const SiteReaction *const reaction);
    void addDimerEvent(const SharedDimer &dimer, const DimerReaction *const reation);

    virtual BaseEventData *randomEvent() const = 0;
    virtual void doWhenEventAddedWithRate(double) {}

private:
    template <class SDData>
    void addEvent(const std::shared_ptr<SDData> &siteOrDimer, const IReactingRole<SDData> *const reaction);

protected:
    std::vector<BaseEventData *> _events;

private:
    double _totalRate;
};

#endif // EVENTBASEDSIMULATION_CONTEXT_H

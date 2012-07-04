#ifndef EVENT_DATA_H
#define EVENT_DATA_H

#include <memory>
#include "baseevent_data.h"
#include "ireacting_role.h"

template <class SDData>
class EventData : public BaseEventData
{
public:
    EventData(const std::shared_ptr<SDData> &siteOrDimer, const IReactingRole<SDData> *reaction, double rate) :
        BaseEventData(rate), _siteOrDimer(siteOrDimer), _reaction(reaction) {}

    void doIt() { _reaction->doIt(_siteOrDimer.get()); }

    SDData *siteOrDimer() const { return _siteOrDimer.get(); }
    IReactingRole<SDData> *reaction() const { return _reaction; }

private:
    std::shared_ptr<SDData> _siteOrDimer;
    const IReactingRole<SDData> *_reaction;
};

#endif // EVENT_DATA_H

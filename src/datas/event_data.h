#ifndef EVENT_DATA_H
#define EVENT_DATA_H

#include "baseevent_data.h"
#include "reaction_data.h"

template <class SData>
class EventData : public BaseEventData
{
public:
    EventData(SData *const site, const ReactionData<SData> *reaction, long double rate) :
        BaseEventData(rate), _site(site), _reaction(reaction) {}

    void doIt() { _reaction->doIt(_site); }
    EventInfoData info(long double dt) const {
        EventInfoData ei(dt);
        ei.set(_site);
        return ei;
    }

    SData *site() const { return _site; }
//    ReactionData<SData> *reaction() const { return _reaction; }

    void update() { resetRate(_reaction->rate(_site)); }

private:
    SData *const _site;
    const ReactionData<SData> *_reaction;
};

#endif // EVENT_DATA_H

#ifndef EVENT_H
#define EVENT_H

#include <memory>
#include "baseevent.h"
#include "reaction_data.h"

template <class SData>
class Event : public BaseEvent
{
public:
    Event(SData *const site, const ReactionData<SData> *reaction, double rate) :
        BaseEvent(rate), _site(site), _reaction(reaction) {}

    void doIt() { _reaction->doIt(_site); }

//    SData *site() const { return _site.get(); }
//    ReactionData<SData> *reaction() const { return _reaction; }

private:
    SData *const _site;
    const ReactionData<SData> *_reaction;
};

#endif // EVENT_H

#ifndef EVENT_H
#define EVENT_H

#include <memory>
#include "baseevent.h"
#include "ireacting_role.h"

template <class SData>
class Event : public BaseEvent
{
public:
    Event(SData *const site, const IReactingRole<SData> *reaction, double rate) :
        BaseEvent(rate), _site(site), _reaction(reaction) {}

    void doIt() { _reaction->doIt(_site); }

//    SData *site() const { return _site.get(); }
//    IReactingRole<SData> *reaction() const { return _reaction; }

private:
    SData *const _site;
    const IReactingRole<SData> *_reaction;
};

#endif // EVENT_H

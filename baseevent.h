#ifndef BASEEVENT_H
#define BASEEVENT_H

#include "eventinfo_data.h"

class BaseEvent
{
public:
    BaseEvent(long double rate) : _rate(rate) {}
    virtual ~BaseEvent() {}

    virtual void doIt() = 0;
    virtual EventInfoData info(long double dt) const = 0;
    long double rate() const { return _rate; }

private:
    long double _rate;
};

#endif // BASEEVENT_H

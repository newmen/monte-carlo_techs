#ifndef BASEEVENT_H
#define BASEEVENT_H

#include "eventinfo_data.h"

class BaseEvent
{
public:
    BaseEvent(double rate) : _rate(rate) {}
    virtual ~BaseEvent() {}

    virtual void doIt() = 0;
    virtual EventInfoData info(double dt) const = 0;
    double rate() const { return _rate; }

private:
    double _rate;
};

#endif // BASEEVENT_H

#ifndef BASEEVENT_DATA_H
#define BASEEVENT_DATA_H

#include "eventinfo_data.h"

class BaseEventData
{
public:
    BaseEventData(long double rate) : _rate(rate) {}
    virtual ~BaseEventData() {}

    virtual void doIt() = 0;
    virtual EventInfoData info(long double dt) const = 0;
    long double rate() const { return _rate; }

protected:
    void resetRate(long double rate) { _rate = rate; }

private:
    long double _rate;
};

#endif // BASEEVENT_DATA_H

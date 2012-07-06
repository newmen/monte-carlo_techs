#ifndef BASEEVENT_H
#define BASEEVENT_H

class BaseEvent
{
public:
    BaseEvent(double rate) : _rate(rate) {}
    virtual ~BaseEvent() {}

    virtual void doIt() = 0;
    double rate() const { return _rate; }

private:
    double _rate;
};

#endif // BASEEVENT_H

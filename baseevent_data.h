#ifndef BASEEVENT_DATA_H
#define BASEEVENT_DATA_H

class BaseEventData
{
public:
    BaseEventData(double rate) : _rate(rate) {}
    virtual ~BaseEventData() {}

    virtual void doIt() = 0;
    double rate() const { return _rate; }

private:
    double _rate;
};

#endif // BASEEVENT_DATA_H

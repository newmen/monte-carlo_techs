#ifndef EVENT_DATA_H
#define EVENT_DATA_H

#include <memory>
#include "ireacting_role.h"

class EventData
{
public:
    EventData(const std::shared_ptr<SiteData> &site, IReactingRole *reaction, float rate);

    SiteData *site() const { return _site.get(); }
    IReactingRole *reaction() const { return _reaction; }
    float rate() const { return _rate; }

private:
    std::shared_ptr<SiteData> _site;
    IReactingRole * _reaction;
    float _rate;
};

#endif // EVENT_DATA_H

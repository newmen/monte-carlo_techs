#include "event_data.h"

EventData::EventData(const std::shared_ptr<SiteData> &site, IReactingRole *reaction, double rate) :
    _site(site), _reaction(reaction), _rate(rate) {}

#ifndef DIMER_DATA_H
#define DIMER_DATA_H

#include <memory>
#include "site_data.h"

class DimerData
{
public:
    DimerData(const SharedSite &first, const SharedSite &second) :
        _first(first), _second(second) {}

    SiteData &first() const { return *_first; }
    SiteData &second() const { return *_second; }

private:
    SharedSite _first, _second;
};

typedef std::shared_ptr<DimerData> SharedDimer;

#endif // DIMER_DATA_H

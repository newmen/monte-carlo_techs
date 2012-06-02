#ifndef IREACTING_ROLE_H
#define IREACTING_ROLE_H

#include "site_data.h"

class IReactingRole
{
public:
    virtual ~IReactingRole() {}

    virtual float rate() const = 0;
    virtual int couldBe(const SiteData &site) const = 0;
    virtual void doIt(SiteData *site) = 0;
};

#endif // IREACTING_ROLE_H

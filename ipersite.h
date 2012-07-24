#ifndef IPERSITE_H
#define IPERSITE_H

#include "simulationbase_context.h"

class IPerSite
{
public:
    virtual ~IPerSite() {}

    virtual long double commonRate() const = 0;
    virtual void doReaction(const SimulationBaseContext *simulationContext, long double r) = 0;

protected:
    IPerSite() {}
};

#endif // IPERSITE_H

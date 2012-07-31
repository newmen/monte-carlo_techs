#ifndef BASEPERSITE_DATA_H
#define BASEPERSITE_DATA_H

#include "../contexts/basesimulation_context.h"

class BasePerSiteData
{
public:
    virtual ~BasePerSiteData() {}

    virtual long double commonRate() const = 0;
    virtual void doReaction(const BaseSimulationContext *simulationContext, long double r) = 0;

protected:
    BasePerSiteData() {}
};

#endif // BASEPERSITE_DATA_H

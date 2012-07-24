#ifndef INODES_H
#define INODES_H

#include "simulationbase_context.h"
#include "nodebase.h"

class INodeS : public NodeBase
{
public:
    virtual void initSum() = 0;
    virtual void doReaction(const SimulationBaseContext *simulationContext, long double r) = 0;

protected:
    INodeS() : NodeBase(0) {}
};

#endif // INODES_H

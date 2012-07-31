#ifndef NODESITE_DATA_H
#define NODESITE_DATA_H

#include "basenode_data.h"
#include "../contexts/basesimulation_context.h"

class NodeSite : public BaseNodeData
{
public:
    virtual void initSum() = 0;
    virtual void doReaction(const BaseSimulationContext *simulationContext, long double r) = 0;

protected:
    NodeSite() : BaseNodeData(0) {}
};

#endif // NODESITE_DATA_H

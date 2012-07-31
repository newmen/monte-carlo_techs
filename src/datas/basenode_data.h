#ifndef BASENODE_DATA_H
#define BASENODE_DATA_H

#include "../contexts/basesimulation_context.h"

class BaseNodeData
{
public:
    virtual ~BaseNodeData() {}

    void setParent(BaseNodeData *parent) { _parent = parent; }
    int level() const { return _level; }
    long double sum() const { return _sum; }

    void accSum(long double sum);

    virtual void reCount(const BaseSimulationContext *simulationContext) = 0;
    virtual bool diagnoze() const = 0;

protected:
    BaseNodeData(int level);

    BaseNodeData *parent() const { return _parent; }

    bool lessThanEps(long double ds) const;

    long double _sum;

private:
    BaseNodeData *_parent;
    int _level;
};

#endif // BASENODE_DATA_H

#ifndef NODEBASE_H
#define NODEBASE_H

#include "simulationbase_context.h"

class NodeBase
{
public:
    virtual ~NodeBase() {}

    void setParent(NodeBase *parent) { _parent = parent; }
    int level() const { return _level; }
    long double sum() const { return _sum; }

    void accSum(long double sum);

    virtual void reCount(const SimulationBaseContext *simulationContext) = 0;
    virtual bool diagnoze() const = 0;

protected:
    NodeBase(int level);

    NodeBase *parent() const { return _parent; }

    bool lessThanEps(long double ds) const;

    long double _sum;

private:
    NodeBase *_parent;
    int _level;
};

#endif // NODEBASE_H

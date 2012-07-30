#ifndef NODEN_H
#define NODEN_H

#include "nodebase.h"
#include "inodes.h"

class NodeN : public NodeBase
{
public:
    NodeN(int width, int level);
    ~NodeN();

    void add(INodeS *node);
    void add(NodeN *node);
    bool isFull() const;

    INodeS *find(long double *r) const;

    void reCount(const SimulationBaseContext *simulationContext);
    bool diagnoze() const;

private:
    void store(NodeBase *node);
    NodeN *last() const;

private:
    NodeBase **_childs;
    int _width, _numberOfChilds;
};

#endif // NODEN_H

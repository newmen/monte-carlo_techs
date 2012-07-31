#ifndef NODE_DATA_H
#define NODE_DATA_H

#include "basenode_data.h"
#include "nodesite_data.h"

class NodeData : public BaseNodeData
{
public:
    NodeData(int width, int level);
    ~NodeData();

    void add(NodeSite *node);
    void add(NodeData *node);
    bool isFull() const;

    NodeSite *find(long double *r) const;

    void reCount(const BaseSimulationContext *simulationContext);
    bool diagnoze() const;

private:
    void store(BaseNodeData *node);
    NodeData *last() const;

private:
    BaseNodeData **_childs;
    int _width, _numberOfChilds;
};

#endif // NODE_DATA_H

#ifndef MCTREE_DATA_H
#define MCTREE_DATA_H

#include "node_data.h"
#include "nodesite_data.h"
#include "../contexts/basesimulation_context.h"

class MCTreeData
{
public:
    MCTreeData(int width);
    ~MCTreeData();

    void add(NodeSite *node);
    long double sum() const;

    NodeSite *find(long double *r) const;

    void reCount(const BaseSimulationContext *simulationContext);
    bool diagnostic() const;

private:
    int _width;
    NodeData *_root;
};

#endif // MCTREE_DATA_H

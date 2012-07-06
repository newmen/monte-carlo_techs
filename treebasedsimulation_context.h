#ifndef TREEBASEDSIMULATION_CONTEXT_H
#define TREEBASEDSIMULATION_CONTEXT_H

#include "sitebasedsimulation_context.h"
#include "mctree.h"
#include "nodes.h"

int calcTreeWidthByK(int size, float levels);
int optimalTreeWidth(int size);

class TreeBasedSimulationContext : public SiteBasedSimulationContext<NodeS>
{
public:
    TreeBasedSimulationContext(AreaData *area);
    TreeBasedSimulationContext(AreaData *area, float levels);

    double doReaction();

protected:
    void storeCell(NodeS *perCell);

private:
    MCTree _tree;
};

#endif // TREEBASEDSIMULATION_CONTEXT_H

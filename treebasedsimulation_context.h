#ifndef TREEBASEDSIMULATION_CONTEXT_H
#define TREEBASEDSIMULATION_CONTEXT_H

#include <set>
#include "sitebasedsimulation_context.h"
#include "percell.h"
#include "perdimer.h"
#include "mctree.h"
#include "nodes.h"

int calcTreeWidthByK(int size, float levels);
int optimalTreeWidth(int size);

typedef NodeS<PerCell> NodeCell;
typedef NodeS<PerDimer> NodeDimer;

class TreeBasedSimulationContext : public SiteBasedSimulationContext<NodeCell, NodeDimer>
{
public:
    TreeBasedSimulationContext(AreaData *area);
    TreeBasedSimulationContext(AreaData *area, float levels);

    double doReaction();

protected:
    void initData();

    void storeCell(NodeCell *);
    void storeDimer(NodeDimer *perDimer);

private:
    MCTree _tree;
    std::set<NodeCell *> _cacheNodeCells;
};

#endif // TREEBASEDSIMULATION_CONTEXT_H

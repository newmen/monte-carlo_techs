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
    TreeBasedSimulationContext(AreaData *area, const ReactorBaseContext *reactor);
    TreeBasedSimulationContext(AreaData *area, const ReactorBaseContext *reactor, float levels);

    EventInfoData doReaction();

protected:
    void storeCell(NodeCell *) {}
    void storeDimer(NodeDimer *nodeDimer);

private:
    MCTree _tree;
};

#endif // TREEBASEDSIMULATION_CONTEXT_H

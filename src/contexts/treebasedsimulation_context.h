#ifndef TREEBASEDSIMULATION_CONTEXT_H
#define TREEBASEDSIMULATION_CONTEXT_H

#include <set>
#include "sitebasedsimulation_context.h"
#include "../datas/percell_data.h"
#include "../datas/perdimer_data.h"
#include "../datas/mctree_data.h"
#include "../roles/node_role.h"

int calcTreeWidthByK(int size, float levels);
int optimalTreeWidth(int size);

typedef NodeRole<PerCellData> NodeCell;
typedef NodeRole<PerDimerData> NodeDimer;

class TreeBasedSimulationContext : public SiteBasedSimulationContext<NodeCell, NodeDimer>
{
public:
    TreeBasedSimulationContext(AreaData *area, const BaseReactorContext *reactor);
    TreeBasedSimulationContext(AreaData *area, const BaseReactorContext *reactor, float levels);

    EventInfoData doReaction();

protected:
    void storeCell(NodeCell *) {}
    void storeDimer(NodeDimer *nodeDimer);

private:
    MCTreeData _tree;
};

#endif // TREEBASEDSIMULATION_CONTEXT_H

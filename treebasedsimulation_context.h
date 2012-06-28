#ifndef TREEBASEDSIMULATION_CONTEXT_H
#define TREEBASEDSIMULATION_CONTEXT_H

#include <map>
#include <set>
#include "simulationbase_context.h"
#include "mctree.h"

int calcTreeWidthByK(int size, float K);
int optimalTreeWidth(int size);

class TreeBasedSimulationContext : public SimulationBaseContext
{
    typedef NodeS SiteNode;
    typedef std::set<const SiteNode *> SiteNodeCache;

public:
    TreeBasedSimulationContext(int width, AreaData *area);

    double doReaction();

private:
    void updateRates(SiteNode *siteNode) const;
    void depthUpdate(SiteNodeCache *cache, SiteNode *siteNode, int depth = 2);

private:
    MCTree _tree;
    std::map<const int *, SiteNode *> _cellsToNodes;
};

#endif // TREEBASEDSIMULATION_CONTEXT_H

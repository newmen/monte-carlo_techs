#ifndef TREEBASEDSIMULATION_CONTEXT_H
#define TREEBASEDSIMULATION_CONTEXT_H

#include <map>
#include <set>
#include "mctree.h"
#include "nodes.h"
#include "perdatasimulation_context.h"
#include "persiteordimer_data.h"

int calcTreeWidthByK(int size, float levels);
int optimalTreeWidth(int size);

class TreeBasedSimulationContext : public PerDataSimulationContext
{
    typedef NodeS<PerSite> SiteNode;
    typedef NodeS<PerDimer> DimerNode;

public:
    TreeBasedSimulationContext(AreaData *area);
    TreeBasedSimulationContext(AreaData *area, float levels);

    double doReaction();

protected:
    PerSite *createData(const SharedSite &site) const;
    PerDimer *createData(const SharedDimer &dimer) const;

    void store(PerSite *perSite);
    void store(PerDimer *perDimer);

private:
    template <class SDData>
    void doReactionAndUpdateTree(MCTree<SDData> *tree, double r);

private:
    MCTree<PerSite> _sitesTree;
    MCTree<PerDimer> _dimersTree;
};

#endif // TREEBASEDSIMULATION_CONTEXT_H

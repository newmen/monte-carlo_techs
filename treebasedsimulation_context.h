#ifndef TREEBASEDSIMULATION_CONTEXT_H
#define TREEBASEDSIMULATION_CONTEXT_H

#include <map>
#include <set>
#include "simulationbase_context.h"
#include "mctree.h"

template <int treeBaseWidth>
class TreeBasedSimulationContext : public SimulationBaseContext
{
public:
    TreeBasedSimulationContext(AreaData *area);

    float doReaction();

private:
    typedef NodeS<REACTIONS_NUM> SiteNode;
    typedef std::set<const SiteNode *> Cache;

    void updateRates(SiteNode *siteNode) const;
    void depthUpdate(Cache *cache, SiteNode *siteNode, int depth = 2);

    MCTree<treeBaseWidth> _tree;
    std::map<const int *, SiteNode *> _cellsToNodes;
};

template <int treeBaseWidth>
TreeBasedSimulationContext<treeBaseWidth>::TreeBasedSimulationContext(AreaData *area) : SimulationBaseContext(area) {
    throughArea([this](int *cell, int **neighbours) {
        SiteNode *siteNode = new SiteNode(cell, neighbours); // was deleted into MCTree
        this->updateRates(siteNode);
        this->_cellsToNodes[cell] = siteNode;
        this->_tree.add(siteNode);
    });
}

template <int treeBaseWidth>
float TreeBasedSimulationContext<treeBaseWidth>::doReaction() {
    float totalRate = _tree.sum();
    if (totalRate == 0) return 0;

    float r = randomN01() * totalRate;
    SiteNode *currentSiteNode = static_cast<SiteNode *>(_tree.find(&r)); // here r is decreasing when we finds necessary site
    int reactionIndex = currentSiteNode->reactionIndex(r);

    reaction(reactionIndex)->doIt(&currentSiteNode->_site);

    Cache cache;
    depthUpdate(&cache, currentSiteNode);

    return negativLogU() / totalRate;
}

template <int treeBaseWidth>
void TreeBasedSimulationContext<treeBaseWidth>::updateRates(TreeBasedSimulationContext<treeBaseWidth>::SiteNode *siteNode) const {
    for (int i = 0; i < REACTIONS_NUM; ++i) {
        IReactingRole *currReaction = reaction(i);
        siteNode->_rates[i] = currReaction->couldBe(siteNode->_site) * currReaction->rate();
    }
    siteNode->updateSum();
}

template <int treeBaseWidth>
void TreeBasedSimulationContext<treeBaseWidth>::depthUpdate(Cache *cache, SiteNode *siteNode, int depth) {
    if (cache->find(siteNode) != cache->end()) return;
    cache->insert(siteNode);

    updateRates(siteNode);
    if (depth == 0) return;

    siteNode->_site.neighboursIterator([this, &cache, &depth](int *neighbourCell) {
        this->depthUpdate(cache, this->_cellsToNodes[neighbourCell], depth - 1);
    });

}

#endif // TREEBASEDSIMULATION_CONTEXT_H

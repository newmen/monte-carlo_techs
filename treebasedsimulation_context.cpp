#include "treebasedsimulation_context.h"
#include <cmath>

int calcTreeWidthByK(int size, float K) {
    double floatWidth = pow(size, K);
    return ((int)(floatWidth * size) == size * (int)(floatWidth)) ? (int)floatWidth : (int)floatWidth + 1;
}

int optimalTreeWidth(int size) {
    return calcTreeWidthByK(size, (double)1 / 4.321);
}

TreeBasedSimulationContext::TreeBasedSimulationContext(int width, AreaData *area) :
    SimulationBaseContext(area), _tree(width)
{
    throughArea([this](int *cell, int **neighbours) {
        SiteNode *siteNode = new SiteNode(cell, neighbours, this->reactionsNum()); // will be deleted into MCTree
        this->updateRates(siteNode);
        this->_cellsToNodes[cell] = siteNode;
        this->_tree.add(siteNode);
    });
}

double TreeBasedSimulationContext::doReaction() {
    double totalRate = _tree.sum();
    if (totalRate == 0) return 0;

    double r = randomN01() * totalRate;
    SiteNode *currentSiteNode = static_cast<SiteNode *>(_tree.find(&r)); // here r is decreasing when we finds necessary site

    if (currentSiteNode == 0) {
        _tree.diagnostic();
    }

    int reactionIndex = currentSiteNode->reactionIndex(r);

    reaction(reactionIndex)->doIt(&currentSiteNode->site());

    SiteNodeCache cache;
    depthUpdate(&cache, currentSiteNode);

    return negativLogU() / totalRate;
}

void TreeBasedSimulationContext::updateRates(TreeBasedSimulationContext::SiteNode *siteNode) const {
    for (int i = 0; i < reactionsNum(); ++i) {
        IReactingRole *currentReaction = reaction(i);
        siteNode->rate(i, currentReaction->couldBe(siteNode->site()) * currentReaction->rate());
    };
    siteNode->updateSum();
}

void TreeBasedSimulationContext::depthUpdate(SiteNodeCache *cache, SiteNode *siteNode, int depth) {
    if (cache->find(siteNode) != cache->end()) return;
    cache->insert(siteNode);

    updateRates(siteNode);
    if (depth == 0) return;

    siteNode->site().neighboursIterator([this, &cache, &depth](int *neighbourCell) {
        this->depthUpdate(cache, this->_cellsToNodes[neighbourCell], depth - 1);
    });

}

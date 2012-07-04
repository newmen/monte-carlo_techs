#include "treebasedsimulation_context.h"
#include <cmath>

int calcTreeWidthByK(int size, float levels) {
    double floatWidth = pow(size, (double)1 / levels);
    return ((int)(floatWidth * size) == size * (int)(floatWidth)) ? (int)floatWidth : (int)floatWidth + 1;
}

int optimalTreeWidth(int size) {
    return calcTreeWidthByK(size, 4);
}

TreeBasedSimulationContext::TreeBasedSimulationContext(AreaData *area) :
    PerDataSimulationContext(area),
    _sitesTree(optimalTreeWidth(area->sizeX() * area->sizeY())),
    _dimersTree(optimalTreeWidth(area->sizeX() * area->sizeY() * 4))
{
    reviewAllEvents();
}

TreeBasedSimulationContext::TreeBasedSimulationContext(AreaData *area, float levels) :
    PerDataSimulationContext(area),
    _sitesTree(calcTreeWidthByK(area->sizeX() * area->sizeY(), levels)),
    _dimersTree(calcTreeWidthByK(area->sizeX() * area->sizeY() * 4, levels))
{
    reviewAllEvents();
}

double TreeBasedSimulationContext::doReaction() {
    double totalRate = _sitesTree.sum() + _dimersTree.sum();
    if (totalRate == 0) return 0;

    double r = randomN01() * totalRate;
    if (r < _sitesTree.sum()) doReactionAndUpdateTree(&_sitesTree, r);
    else doReactionAndUpdateTree(&_dimersTree, r);

    return negativLogU() / totalRate;
}

PerDataSimulationContext::PerSite *TreeBasedSimulationContext::createData(const SharedSite &site) const {
    return new SiteNode(site); // will be deleted into MCTree
}

PerDataSimulationContext::PerDimer *TreeBasedSimulationContext::createData(const SharedDimer &dimer) const {
    return new DimerNode(dimer); // will be deleted into MCTree
}

void TreeBasedSimulationContext::store(PerSite *perSite) {
    _sitesTree.add(static_cast<SiteNode *>(perSite));
}

void TreeBasedSimulationContext::store(PerDimer *perDimer) {
    _dimersTree.add(static_cast<DimerNode *>(perDimer));
}

template <class PerData>
void TreeBasedSimulationContext::doReactionAndUpdateTree(MCTree<PerData> *tree, double r) {
    auto *node = static_cast<NodeS<PerData> *>(tree->find(&r));
    if (node == 0) {
        tree->diagnostic();
    } else {
        node->doReaction(r);
        node->updateRates();
        updateNeighbours(node);
    }
}

#include "treebasedsimulation_context.h"
#include <cmath>

int calcTreeWidthByK(int size, float levels) {
    double floatWidth = pow(size, (double)1 / levels);
    return ((int)(floatWidth * size) == size * (int)(floatWidth)) ? (int)floatWidth : (int)floatWidth + 1;
}

int optimalTreeWidth(int size) {
    return calcTreeWidthByK(size, 5);
}

TreeBasedSimulationContext::TreeBasedSimulationContext(AreaData *area, const ReactorBaseData *reactor) :
    SiteBasedSimulationContext(area, reactor), _tree(optimalTreeWidth(area->size()))
{
    initData();
}

TreeBasedSimulationContext::TreeBasedSimulationContext(AreaData *area, const ReactorBaseData *reactor, float levels) :
    SiteBasedSimulationContext(area, reactor), _tree(calcTreeWidthByK(area->size(), levels))
{
    initData();
}

double TreeBasedSimulationContext::doReaction() {
//    _tree.diagnostic();
    double totalRate = _tree.sum();
    if (totalRate == 0) return 0;

    double r = randomN01() * totalRate;
    INodeS *currentPerCell = _tree.find(&r);
    currentPerCell->doReactionOnSite(r);

    return negativLogU() / totalRate;
}

void TreeBasedSimulationContext::initData() {
    SiteBasedSimulationContext<NodeCell, NodeDimer>::initData();
    _cacheNodeCells.clear();
}

void TreeBasedSimulationContext::storeCell(NodeCell *) {
}

void TreeBasedSimulationContext::storeDimer(NodeDimer *perDimer) {
    // memory of perSite will be deleted into MCTree
    _tree.add(perDimer);

    auto addNodeCell = [this](PerCell *const perCell) {
        NodeCell *const nodeCell = static_cast<NodeCell *const>(perCell);
        if (_cacheNodeCells.find(nodeCell) == _cacheNodeCells.cend()) {
            _cacheNodeCells.insert(nodeCell);
            _tree.add(nodeCell);
        }
    };

    addNodeCell(perDimer->first());
    addNodeCell(perDimer->second());
}

#include "treebasedsimulation_context.h"
#include <cmath>

int calcTreeWidthByK(int size, float levels) {
    double floatWidth = pow(size, (double)1 / levels);
    return ((int)(floatWidth * size) == size * (int)(floatWidth)) ? (int)floatWidth : (int)floatWidth + 1;
}

int optimalTreeWidth(int size) {
    return calcTreeWidthByK(size, 5);
}

TreeBasedSimulationContext::TreeBasedSimulationContext(AreaData *area, const ReactorBaseContext *reactor) :
    SiteBasedSimulationContext(area, reactor), _tree(optimalTreeWidth(area->size()))
{
    initData();
}

TreeBasedSimulationContext::TreeBasedSimulationContext(AreaData *area, const ReactorBaseContext *reactor, float levels) :
    SiteBasedSimulationContext(area, reactor), _tree(calcTreeWidthByK(area->size(), levels))
{
    initData();
}

EventInfoData TreeBasedSimulationContext::doReaction() {
//    _tree.diagnostic();
    double totalRate = _tree.sum();
    if (totalRate == 0) return EventInfoData(0);

    double r = randomN01() * totalRate;
    INodeS *currentNode = _tree.find(&r);
    currentNode->doReaction(this, r);

    EventInfoData ei(negativLogU() / totalRate);
    NodeCell *nodeCell = dynamic_cast<NodeCell *>(currentNode);
    if (nodeCell) ei.set(nodeCell->site());
    else ei.set(dynamic_cast<NodeDimer *>(currentNode)->site());

    return ei;
}

void TreeBasedSimulationContext::initData() {
    SiteBasedSimulationContext<NodeCell, NodeDimer>::initData();
    _cacheNodeCells.clear();
}

void TreeBasedSimulationContext::storeDimer(NodeDimer *perDimer) {
    // memory of each perSite will be deleted into MCTree
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

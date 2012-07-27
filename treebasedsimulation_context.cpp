#include <cmath>
#include "treebasedsimulation_context.h"

#include <iostream>

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
//    if (!_tree.diagnostic()) return EventInfoData(0);

    bool isRealyOver = false;
    while (true) {
        long double totalRate = _tree.sum();
        if (totalRate == 0.0) {
            if (isRealyOver) break;
            else {
                std::cout << "ONE TIME! -> _tree.reCount()" << std::endl;
                isRealyOver = true;
                _tree.reCount();
                continue;
            }
        }
        isRealyOver = false;

        long double r = randomN01() * totalRate;
        INodeS *currentNode = _tree.find(&r);
        if (currentNode == 0) {
            _tree.reCount();
            continue;
        }
        currentNode->doReaction(this, r);

        EventInfoData ei(negativLogU() / totalRate);
        NodeCell *nodeCell = dynamic_cast<NodeCell *>(currentNode);
        if (nodeCell) ei.set(nodeCell->site());
        else ei.set(dynamic_cast<NodeDimer *>(currentNode)->site());

        return ei;
    }
    return EventInfoData(0);
}

void TreeBasedSimulationContext::storeDimer(NodeDimer *nodeDimer) {
    static int n = 0;

    // memory of each perSite will be deleted into MCTree
    _tree.add(nodeDimer);
    if (n++ % 2 == 0) {
        NodeCell *const nodeCell = static_cast<NodeCell *const>(nodeDimer->first());
        _tree.add(nodeCell);
    }
}

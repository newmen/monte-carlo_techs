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
    SiteBasedSimulationContext<NodeS>(area),
    _tree(optimalTreeWidth(area->sizeX() * area->sizeY()))
{
    initData();
}

TreeBasedSimulationContext::TreeBasedSimulationContext(AreaData *area, float levels) :
    SiteBasedSimulationContext<NodeS>(area),
    _tree(calcTreeWidthByK(area->sizeX() * area->sizeY(), levels))
{
    initData();
}

double TreeBasedSimulationContext::doReaction() {
//    _tree.diagnostic();
    double totalRate = _tree.sum();
    if (totalRate == 0) return 0;

    double r = randomN01() * totalRate;
    NodeS *currentPerCell = _tree.find(&r);
    currentPerCell->doReaction(r);

    return negativLogU() / totalRate;
}

void TreeBasedSimulationContext::storeCell(NodeS *perCell) {
    _tree.add(perCell); // memory of perCell will be deleted into MCTree
}

#include "treesimcontextfactory.h"

#include "../treebasedsimulation_context.h"

TreeSimContextFactory::TreeSimContextFactory(int treeWidth) : _treeWidth(treeWidth) {}

SimulationBaseContext *TreeSimContextFactory::createContext(AreaData *area) const {
    return new TreeBasedSimulationContext(_treeWidth, area);
}

void TreeSimContextFactory::setWidth(int treeWidth) {
    _treeWidth = treeWidth;
}

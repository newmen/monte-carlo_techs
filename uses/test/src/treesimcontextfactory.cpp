#include "treesimcontextfactory.h"

#include <contexts/treebasedsimulation_context.h>

TreeSimContextFactory::TreeSimContextFactory(int levels) : _levels(levels) {}

BaseSimulationContext *TreeSimContextFactory::createContext(AreaData *area, const BaseReactorContext *reactor) const {
    return new TreeBasedSimulationContext(area, reactor, _levels);
}

void TreeSimContextFactory::setWidth(int levels) {
    _levels = levels;
}

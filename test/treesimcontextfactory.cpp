#include "treesimcontextfactory.h"

#include "../treebasedsimulation_context.h"

TreeSimContextFactory::TreeSimContextFactory(ReactorBaseData *reactor, int levels) :
    SimulationContextFactory(reactor), _levels(levels) {}

SimulationBaseContext *TreeSimContextFactory::createContext(AreaData *area) const {
    return new TreeBasedSimulationContext(area, reactor(), _levels);
}

void TreeSimContextFactory::setWidth(int levels) {
    _levels = levels;
}

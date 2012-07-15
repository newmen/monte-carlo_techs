#include "simulationcontextfactory.h"

SimulationContextFactory::SimulationContextFactory(ReactorBaseData *reactor) :
    _reactor(reactor) {}

//SimulationContextFactory::~SimulationContextFactory() {}

const ReactorBaseData *SimulationContextFactory::reactor() const {
    return _reactor;
}

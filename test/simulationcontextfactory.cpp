#include "simulationcontextfactory.h"
#include "../abcdcellreactor_data.h"
#include "../abcddimerreactor_data.h"

SimulationContextFactory::SimulationContextFactory() {
    _reactor = new ABCDCellReactorData();
}

SimulationContextFactory::~SimulationContextFactory() {
    delete _reactor;
}

const ReactorBaseData *SimulationContextFactory::reactor() const {
    return _reactor;
}

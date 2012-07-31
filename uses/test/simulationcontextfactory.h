#ifndef SIMULATIONCONTEXTFACTORY_H
#define SIMULATIONCONTEXTFACTORY_H

#include "../../src/datas/area_data.h"
#include "../../src/contexts/basereactor_context.h"
#include "../../src/contexts/basesimulation_context.h"

class SimulationContextFactory
{
public:
    virtual ~SimulationContextFactory() {}
    virtual BaseSimulationContext *createContext(AreaData *area, const BaseReactorContext *reactor) const = 0;

protected:
    SimulationContextFactory() {}
};

#endif // SIMULATIONCONTEXTFACTORY_H

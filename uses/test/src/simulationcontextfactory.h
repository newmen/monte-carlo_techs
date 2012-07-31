#ifndef SIMULATIONCONTEXTFACTORY_H
#define SIMULATIONCONTEXTFACTORY_H

#include <datas/area_data.h>
#include <contexts/basereactor_context.h>
#include <contexts/basesimulation_context.h>

class SimulationContextFactory
{
public:
    virtual ~SimulationContextFactory() {}
    virtual BaseSimulationContext *createContext(AreaData *area, const BaseReactorContext *reactor) const = 0;

protected:
    SimulationContextFactory() {}
};

#endif // SIMULATIONCONTEXTFACTORY_H

#ifndef SIMULATIONCONTEXTFACTORY_H
#define SIMULATIONCONTEXTFACTORY_H

#include "../area_data.h"
#include "../simulationbase_context.h"
#include "../reactorbase_context.h"

class SimulationContextFactory
{
public:
    virtual ~SimulationContextFactory() {}
    virtual SimulationBaseContext *createContext(AreaData *area, const ReactorBaseContext *reactor) const = 0;

protected:
    SimulationContextFactory() {}
};

#endif // SIMULATIONCONTEXTFACTORY_H

#ifndef SIMULATIONCONTEXTFACTORY_H
#define SIMULATIONCONTEXTFACTORY_H

#include "../area_data.h"
#include "../simulationbase_context.h"
#include "../reactorbase_data.h"

class SimulationContextFactory
{
public:
    virtual ~SimulationContextFactory() {}
    virtual SimulationBaseContext *createContext(AreaData *area) const = 0;

protected:
    SimulationContextFactory(ReactorBaseData *reactor);
    const ReactorBaseData *reactor() const;

private:
    const ReactorBaseData *_reactor;
};

#endif // SIMULATIONCONTEXTFACTORY_H

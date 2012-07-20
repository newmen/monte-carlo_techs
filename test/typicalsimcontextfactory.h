#ifndef TYPICALSIMCONTEXTFACTORY_H
#define TYPICALSIMCONTEXTFACTORY_H

#include "simulationcontextfactory.h"

template <class SimulationContext>
class TypicalSimContextFactory : public SimulationContextFactory
{
public:
    SimulationBaseContext *createContext(AreaData *area, const ReactorBaseContext *reactor) const;
};

template <class SimulationContext>
SimulationBaseContext *TypicalSimContextFactory<SimulationContext>::createContext(AreaData *area, const ReactorBaseContext *reactor) const {
    return new SimulationContext(area, reactor);
}

#endif // TYPICALSIMCONTEXTFACTORY_H

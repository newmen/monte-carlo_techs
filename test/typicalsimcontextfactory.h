#ifndef TYPICALSIMCONTEXTFACTORY_H
#define TYPICALSIMCONTEXTFACTORY_H

#include "simulationcontextfactory.h"

template <class SimulationContext>
class TypicalSimContextFactory : public SimulationContextFactory
{
public:
    TypicalSimContextFactory() {}

    SimulationBaseContext *createContext(AreaData *area) const;
};

template <class SimulationContext>
SimulationBaseContext *TypicalSimContextFactory<SimulationContext>::createContext(AreaData *area) const {
    return new SimulationContext(area);
}

#endif // TYPICALSIMCONTEXTFACTORY_H

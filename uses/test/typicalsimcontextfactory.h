#ifndef TYPICALSIMCONTEXTFACTORY_H
#define TYPICALSIMCONTEXTFACTORY_H

#include "simulationcontextfactory.h"

template <class SimulationContext>
class TypicalSimContextFactory : public SimulationContextFactory
{
public:
    BaseSimulationContext *createContext(AreaData *area, const BaseReactorContext *reactor) const;
};

template <class SimulationContext>
BaseSimulationContext *TypicalSimContextFactory<SimulationContext>::createContext(AreaData *area, const BaseReactorContext *reactor) const {
    return new SimulationContext(area, reactor);
}

#endif // TYPICALSIMCONTEXTFACTORY_H

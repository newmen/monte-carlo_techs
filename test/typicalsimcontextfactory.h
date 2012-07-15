#ifndef TYPICALSIMCONTEXTFACTORY_H
#define TYPICALSIMCONTEXTFACTORY_H

#include "simulationcontextfactory.h"

template <class SimulationContext>
class TypicalSimContextFactory : public SimulationContextFactory
{
public:
    TypicalSimContextFactory(ReactorBaseData *reactor);

    SimulationBaseContext *createContext(AreaData *area) const;
};

template <class SimulationContext>
TypicalSimContextFactory<SimulationContext>::TypicalSimContextFactory(ReactorBaseData *reactor) :
    SimulationContextFactory(reactor) {}

template <class SimulationContext>
SimulationBaseContext *TypicalSimContextFactory<SimulationContext>::createContext(AreaData *area) const {
    return new SimulationContext(area, reactor());
}

#endif // TYPICALSIMCONTEXTFACTORY_H

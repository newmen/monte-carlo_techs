#ifndef TREESIMCONTEXTFACTORY_H
#define TREESIMCONTEXTFACTORY_H

#include "simulationcontextfactory.h"

class TreeSimContextFactory : public SimulationContextFactory
{
public:
    TreeSimContextFactory(int levels);

    BaseSimulationContext *createContext(AreaData *area, const BaseReactorContext *reactor) const;
    void setWidth(int levels);

private:
    int _levels;
};

#endif // TREESIMCONTEXTFACTORY_H

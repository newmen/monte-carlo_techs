#ifndef TREESIMCONTEXTFACTORY_H
#define TREESIMCONTEXTFACTORY_H

#include "simulationcontextfactory.h"

class TreeSimContextFactory : public SimulationContextFactory
{
public:
    TreeSimContextFactory(ReactorBaseData *reactor, int levels);

    SimulationBaseContext *createContext(AreaData *area) const;
    void setWidth(int levels);

private:
    int _levels;
};

#endif // TREESIMCONTEXTFACTORY_H

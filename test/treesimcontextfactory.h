#ifndef TREESIMCONTEXTFACTORY_H
#define TREESIMCONTEXTFACTORY_H

#include "simulationcontextfactory.h"

class TreeSimContextFactory : public SimulationContextFactory
{
public:
    TreeSimContextFactory(int treeWidth);

    SimulationBaseContext *createContext(AreaData *area) const;
    void setWidth(int treeWidth);

private:
    int _treeWidth;
};

#endif // TREESIMCONTEXTFACTORY_H

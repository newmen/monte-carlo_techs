#ifndef SIMULATIONBASE_CONTEXT_H
#define SIMULATIONBASE_CONTEXT_H

#include <functional>
#include <vector>
#include "area_data.h"
#include "ireacting_role.h"

class SimulationBaseContext
{
public:
    SimulationBaseContext(AreaData *area);
    virtual ~SimulationBaseContext();

    virtual double doReaction() = 0;

protected:
    void throughArea(std::function<void (int *cell, int **neighbours)> lambda) const;

    IReactingRole *reaction(int index) const;
    int reactionsNum() const;
    void eachReaction(std::function<void (IReactingRole *const)> lambda) const;

    double randomN01() const;
    double negativLogU() const;

private:
    AreaData *_area;
    std::vector<IReactingRole *> _reactions;
};

#endif // SIMULATIONBASE_CONTEXT_H

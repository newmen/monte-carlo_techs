#ifndef SIMULATIONBASE_CONTEXT_H
#define SIMULATIONBASE_CONTEXT_H

#include <functional>
#include "area_data.h"
#include "ireacting_role.h"

#define REACTIONS_NUM 4

class SimulationBaseContext
{
public:
    SimulationBaseContext(AreaData *area);
    virtual ~SimulationBaseContext();

    virtual float doReaction() = 0;

protected:
    void throughArea(std::function<void (int *cell, int **neighbours)> lambda) const;
    IReactingRole *reaction(int index) const;
    float randomN01() const;

private:
    AreaData *_area;
    IReactingRole *_reactions[REACTIONS_NUM];
};

#endif // SIMULATIONBASE_CONTEXT_H

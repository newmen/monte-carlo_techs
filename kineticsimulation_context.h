#ifndef KINETICSIMULATION_CONTEXT_H
#define KINETICSIMULATION_CONTEXT_H

#include "sitebasedsimulation_context.h"
#include "percell.h"

class KineticSimulationContext : public SiteBasedSimulationContext<PerCell>
{
public:
    KineticSimulationContext(AreaData *area);
    ~KineticSimulationContext();

    double doReaction();

protected:
    void storeCell(PerCell *const perCell);

private:
    PerCell *findMin(double *dt) const;
    void doRandomReaction(PerCell *const perCell);

private:
    std::vector<PerCell *> _perCells;
};

#endif // KINETICSIMULATION_CONTEXT_H

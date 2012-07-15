#ifndef SIMULATIONBASE_CONTEXT_H
#define SIMULATIONBASE_CONTEXT_H

#include <functional>
#include <vector>
#include "reactorbase_data.h"
#include "area_data.h"
#include "cell_data.h"
#include "dimer_data.h"

class SimulationBaseContext
{
public:
    SimulationBaseContext(AreaData *area, const ReactorBaseData *reactor);
    virtual ~SimulationBaseContext();

    virtual double doReaction() = 0;

protected:
    void eachCell(std::function<void (CellData *const)> lambda) const;
    void eachDimer(std::function<void (DimerData *const)> lambda) const;

    void eachCellReaction(std::function<void (const ReactionData<CellData> *const)> lambda) const;
    void eachDimerReaction(std::function<void (const ReactionData<DimerData> *const)> lambda) const;

    double randomN01() const;
    double negativLogU() const;

private:
    AreaData *_area;
    const ReactorBaseData *_reactor;
    std::vector<CellData *> _cells;
    std::vector<DimerData *> _dimers;
};

#endif // SIMULATIONBASE_CONTEXT_H

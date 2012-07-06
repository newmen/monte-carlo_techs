#ifndef SIMULATIONBASE_CONTEXT_H
#define SIMULATIONBASE_CONTEXT_H

#include <functional>
#include <vector>
#include "area_data.h"
#include "cell_data.h"
#include "dimer_data.h"
#include "ireacting_role.h"

class SimulationBaseContext
{
public:
    SimulationBaseContext(AreaData *area);
    virtual ~SimulationBaseContext();

    virtual double doReaction() = 0;

protected:
    typedef IReactingRole<CellData> CellReaction;
    typedef IReactingRole<DimerData> DimerReaction;

    void eachCell(std::function<void (CellData *const)> lambda) const;
    void eachDimer(std::function<void (DimerData *const)> lambda) const;

    void eachCellReaction(std::function<void (const CellReaction *const)> lambda) const;
    void eachDimerReaction(std::function<void (const DimerReaction *const)> lambda) const;

    double randomN01() const;
    double negativLogU() const;

private:
    void initDimers();

private:
    AreaData *_area;
    std::vector<DimerData *> _dimers;
    std::vector<const CellReaction *> _cellReactions;
    std::vector<const DimerReaction *> _dimerReactions;
};

#endif // SIMULATIONBASE_CONTEXT_H

#ifndef SIMULATIONBASE_CONTEXT_H
#define SIMULATIONBASE_CONTEXT_H

#include <functional>
#include <vector>
#include "reactorbase_context.h"
#include "area_data.h"
#include "cell_data.h"
#include "dimer_data.h"
#include "eventinfo_data.h"

class SimulationBaseContext
{
public:
    SimulationBaseContext(AreaData *area, const ReactorBaseContext *reactor);
    virtual ~SimulationBaseContext();

    virtual EventInfoData doReaction() = 0;

    template <class SData>
    void reinitSite(SData *site) const;

protected:
    void eachCell(std::function<void (CellData *const)> lambda) const;
    void eachDimer(std::function<void (DimerData *const)> lambda) const;

    void eachCellReaction(std::function<void (const ReactionData<CellData> *const)> lambda) const;
    void eachDimerReaction(std::function<void (const ReactionData<DimerData> *const)> lambda) const;

    double randomN01() const;
    double negativLogU() const;

private:
    template <class SData>
    void eachSite(const std::vector<SData *> &sites, const std::function<void (SData *const)> &lambda) const;

private:
    AreaData *_area;
    const ReactorBaseContext *_reactor;
    std::vector<CellData *> _cells;
    std::vector<DimerData *> _dimers;
};

#endif // SIMULATIONBASE_CONTEXT_H

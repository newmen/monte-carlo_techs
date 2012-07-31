#ifndef BASESIMULATION_CONTEXT_H
#define BASESIMULATION_CONTEXT_H

#include <functional>
#include <vector>
#include "basereactor_context.h"
#include "../datas/area_data.h"
#include "../datas/cell_data.h"
#include "../datas/dimer_data.h"
#include "../datas/eventinfo_data.h"

class BaseSimulationContext
{
public:
    BaseSimulationContext(AreaData *area, const BaseReactorContext *reactor);
    virtual ~BaseSimulationContext();

    virtual EventInfoData doReaction() = 0;

    template <class SData>
    void reinitSite(SData *site) const;

protected:
    void eachCell(std::function<void (CellData *const)> lambda) const;
    void eachDimer(std::function<void (DimerData *const)> lambda) const;

    void eachCellReaction(std::function<void (const ReactionData<CellData> *const)> lambda) const;
    void eachDimerReaction(std::function<void (const ReactionData<DimerData> *const)> lambda) const;

    long double randomN01() const;
    long double negativLogU() const;

private:
    template <class SData>
    void eachSite(const std::vector<SData *> &sites, const std::function<void (SData *const)> &lambda) const;

private:
    AreaData *_area;
    const BaseReactorContext *_reactor;
    std::vector<CellData *> _cells;
    std::vector<DimerData *> _dimers;
};

#endif // BASESIMULATION_CONTEXT_H

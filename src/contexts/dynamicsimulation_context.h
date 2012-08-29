#ifndef DYNAMICSIMULATION_CONTEXT_H
#define DYNAMICSIMULATION_CONTEXT_H

#include <map>
#include <vector>
#include "simplesimulation_context.h"
#include "../datas/cell_data.h"
#include "../datas/dimer_data.h"

class DynamicSimulationContext : public SimpleSimulationContext
{
    typedef std::map<long double, std::vector<std::pair<CellData *const, const ReactionData<CellData> *const> > > CellsMap;
    typedef std::map<long double, std::vector<std::pair<DimerData *const, const ReactionData<DimerData> *const> > > DimersMap;

public:
    DynamicSimulationContext(AreaData *area, const BaseReactorContext *reactor);
//    ~DynamicSimulationContext();

    EventInfoData doReaction();

protected:
    void clearAllEvents();

    void addCellEvent(CellData *const cell, const ReactionData<CellData> *const reaction);
    void addDimerEvent(DimerData *const dimer, const ReactionData<DimerData> *const reaction);

private:
    template <class SData>
    void addEvent(std::map<long double, std::vector<std::pair<SData *const, const ReactionData<SData> *const> > > *sitesMap, SData *const site, const ReactionData<SData> *const reaction);

    template <class SData>
    SData *findAndDoReaction(long double *r, const std::map<long double, std::vector<std::pair<SData *const, const ReactionData<SData> *const> > > &sitesMap) const;

private:
    CellsMap _cells;
    DimersMap _dimers;

    long double _totalRate;
};

#endif // DYNAMICSIMULATION_CONTEXT_H

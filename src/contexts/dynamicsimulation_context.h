#ifndef DYNAMICSIMULATION_CONTEXT_H
#define DYNAMICSIMULATION_CONTEXT_H

#include <map>
#include <vector>
#include "simplesimulation_context.h"
#include "../datas/cell_data.h"
#include "../datas/dimer_data.h"

class DynamicSimulationContext : public SimpleSimulationContext
{
    typedef std::map<long double, std::vector<std::pair<CellData *, const ReactionData<CellData> *> > > CellsMap;
    typedef std::map<long double, std::vector<std::pair<DimerData *, const ReactionData<DimerData> *> > > DimersMap;

public:
    DynamicSimulationContext(AreaData *area, const BaseReactorContext *reactor);
//    ~DynamicSimulationContext();

    EventInfoData doReaction();

protected:
    void clearAllEvents();

    void addCellEvent(CellData *cell, const ReactionData<CellData> *reaction);
    void addDimerEvent(DimerData *dimer, const ReactionData<DimerData> *reaction);

private:
    template <class SData>
    void addEvent(std::map<long double, std::vector<std::pair<SData *, const ReactionData<SData> *> > > *sitesMap, SData *site, const ReactionData<SData> *reaction);

    template <class SData>
    SData *findAndDoReaction(long double *r, const std::map<long double, std::vector<std::pair<SData *, const ReactionData<SData> *> > > &sitesMap) const;

private:
    CellsMap _cells;
    DimersMap _dimers;

    long double _totalRate;
};

#endif // DYNAMICSIMULATION_CONTEXT_H

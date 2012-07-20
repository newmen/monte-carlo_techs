#ifndef DYNAMICSIMULATION_CONTEXT_H
#define DYNAMICSIMULATION_CONTEXT_H

#include <map>
#include <vector>
#include "simplesimulation_context.h"
#include "cell_data.h"
#include "dimer_data.h"

class DynamicSimulationContext : public SimpleSimulationContext
{
    typedef std::map<const ReactionData<CellData> *const, std::vector<CellData *> > CellsMap;
    typedef std::map<const ReactionData<DimerData> *const, std::vector<DimerData *> > DimersMap;
    typedef std::map<const ReactionData<CellData> *const, double> RatesOnSitesMap;
    typedef std::map<const ReactionData<DimerData> *const, double> RatesOnDimersMap;

public:
    DynamicSimulationContext(AreaData *area, const ReactorBaseContext *reactor);
//    ~DynamicSimulationContext();

    EventInfoData doReaction();

protected:
    void clearAllEvents();

    void addCellEvent(CellData *const cell, const ReactionData<CellData> *const reaction);
    void addDimerEvent(DimerData *const dimer, const ReactionData<DimerData> *const reaction);

private:
    template <class SData>
    void addEvent(std::map<const ReactionData<SData> *const, std::vector<SData *> > *dataContainer, std::map<const ReactionData<SData> *const, double> *rates, SData *const site, const ReactionData<SData> *const reaction);

    template <class SData>
    const ReactionData<SData> *findReaction(double *r, double *max, const std::map<const ReactionData<SData> *const, double> &ratesMap) const;

    template <class SData>
    void clearEvents(std::map<const ReactionData<SData> *const, std::vector<SData *> > *dataContainer, std::map<const ReactionData<SData> *const, double> *rates);

private:
    CellsMap _cells;
    DimersMap _dimers;

    RatesOnSitesMap _ratesOnSites;
    RatesOnDimersMap _ratesOnDimers;

    double _totalRate;
};

#endif // DYNAMICSIMULATION_CONTEXT_H

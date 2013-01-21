#ifndef COMMONOPTIMIZEDEVENTBASEDSIMULATION_CONTEXT_H
#define COMMONOPTIMIZEDEVENTBASEDSIMULATION_CONTEXT_H

#include <map>
#include "optimizedsimplesimulation_context.h"
#include "../datas/event_data.h"

class CommonOptimizedEventBasedSimulationContext : public OptimizedSimpleSimulationContext
{
public:
    EventInfoData doReaction();

protected:
    CommonOptimizedEventBasedSimulationContext(AreaData *area, const BaseReactorContext *reactor);

    long double totalRate() const { return _totalRate; }
    void incTotalRate(long double dRate) { _totalRate += dRate; }
    void clearTotalRate() { _totalRate = 0; }

    void addCellEvent(CellData *const cell, const ReactionData<CellData> *const reaction);
    void addDimerEvent(DimerData *const dimer, const ReactionData<DimerData> *const reation);

    virtual void storeEvent(BaseEventData *event) = 0;
    virtual BaseEventData *randomEvent() const = 0;
    virtual EventInfoData doEvent(BaseEventData *event) = 0;
    virtual void recountTotalRate() = 0;

    long double countAround(CellData *const cell);
    long double countAround(DimerData *const dimer);

private:
    template <class SData>
    void addEvent(SData *const site, const ReactionData<SData> *const reaction);

    template <class SData>
    void assignEventToSite(SData *const site, EventData<SData> *const event);

    template <class SData>
    long double countAroundSite(SData *const site);

protected:
    std::map<CellData *, std::vector<EventData<CellData> *> > _cellEvents;
    std::map<CellData *, long double> _cellRates;
    std::map<DimerData *, std::vector<EventData<DimerData> *> > _dimerEvents;
    std::map<DimerData *, long double> _dimerRates;

private:
    long double _totalRate;
};

#endif // COMMONOPTIMIZEDEVENTBASEDSIMULATION_CONTEXT_H

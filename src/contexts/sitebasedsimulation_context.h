#ifndef SITEBASEDSIMULATION_CONTEXT_H
#define SITEBASEDSIMULATION_CONTEXT_H

#include <map>
#include <vector>
#include "basesimulation_context.h"

template <class SmartCell, class SmartDimer>
class SiteBasedSimulationContext : public BaseSimulationContext
{
protected:
    SiteBasedSimulationContext(AreaData *area, const BaseReactorContext *reactor);

    void initData();

    virtual void storeCell(SmartCell *const perCell) = 0;
    virtual void storeDimer(SmartDimer *const perDimer) = 0;

private:
    void linkPerSites(SmartCell *const perCell, SmartDimer *const perDimer) const;
};

template <class SmartCell, class SmartDimer>
SiteBasedSimulationContext<SmartCell, SmartDimer>::SiteBasedSimulationContext(AreaData *area, const BaseReactorContext *reactor) :
    BaseSimulationContext(area, reactor) {}

template <class SmartCell, class SmartDimer>
void SiteBasedSimulationContext<SmartCell, SmartDimer>::initData() {
    std::map<CellData *const, SmartCell *> cellsToPerCells;
    eachCell([this, &cellsToPerCells](CellData *const cell) {
        SmartCell *perCell = new SmartCell(cell);
        this->eachCellReaction([this, &perCell](const ReactionData<CellData> *const reaction) {
            perCell->addReaction(reaction);
        });
        cellsToPerCells[cell] = perCell;
        this->storeCell(perCell);
    });

    eachDimer([this, &cellsToPerCells](DimerData *const dimer) {
        SmartDimer *perDimer = new SmartDimer(dimer);
        this->eachDimerReaction([this, &perDimer](const ReactionData<DimerData> *const reaction) {
            perDimer->addReaction(reaction);
        });
        this->linkPerSites(cellsToPerCells.find(dimer->first)->second, perDimer);
        this->linkPerSites(cellsToPerCells.find(dimer->second)->second, perDimer);
        this->storeDimer(perDimer);
    });
}

template <class SmartCell, class SmartDimer>
void SiteBasedSimulationContext<SmartCell, SmartDimer>::linkPerSites(SmartCell *const perCell, SmartDimer *const perDimer) const {
    perDimer->addPerCell(perCell);
    perCell->addPerDimer(perDimer);
}

#endif // SITEBASEDSIMULATION_CONTEXT_H

#ifndef SITEBASEDSIMULATION_CONTEXT_H
#define SITEBASEDSIMULATION_CONTEXT_H

#include <vector>
#include "simulationbase_context.h"
#include "perdimer.h"

template <class SmartCell>
class SiteBasedSimulationContext : public SimulationBaseContext
{
public:
    ~SiteBasedSimulationContext();

protected:
    SiteBasedSimulationContext(AreaData *area);

    void initData();

    virtual void storeCell(SmartCell *const perCell) = 0;

private:
    void linkPerSites(SmartCell *const perCell, PerDimer *const perDimer) const;

private:
    std::vector<PerDimer *> _perDimers;
};

template <class SmartCell>
SiteBasedSimulationContext<SmartCell>::SiteBasedSimulationContext(AreaData *area) :
    SimulationBaseContext(area) {}

template <class SmartCell>
void SiteBasedSimulationContext<SmartCell>::initData() {
    std::map<CellData *const, SmartCell *> cellsToPerCells;
    eachCell([this, &cellsToPerCells](CellData *const cell) {
        SmartCell *perCell = new SmartCell(cell);
        this->eachCellReaction([this, &perCell](const IReactingRole<CellData> *const reaction) {
            perCell->addReaction(reaction);
        });
        // более оптимально для кинетического алгоритма, вызывать storeCell здесь

        cellsToPerCells[cell] = perCell;
    });

    eachDimer([this, &cellsToPerCells](DimerData *const dimer) {
        PerDimer *perDimer = new PerDimer(dimer);
        this->eachDimerReaction([this, &perDimer](const IReactingRole<DimerData> *const reaction) {
            perDimer->addReaction(reaction);
        });
        this->_perDimers.push_back(perDimer);

        this->linkPerSites(cellsToPerCells.find(dimer->first)->second, perDimer);
        this->linkPerSites(cellsToPerCells.find(dimer->second)->second, perDimer);
    });

    // цикл не оптимален для кинетического алгоритма (см. коммент выше)
    for (auto p = cellsToPerCells.cbegin(); p != cellsToPerCells.cend(); ++p) {
        storeCell(p->second);
    }
}

template <class SmartCell>
SiteBasedSimulationContext<SmartCell>::~SiteBasedSimulationContext() {
    for (auto p = _perDimers.begin(); p != _perDimers.end(); ++p) delete *p;
}

template <class SmartCell>
void SiteBasedSimulationContext<SmartCell>::linkPerSites(SmartCell *const perCell, PerDimer *const perDimer) const {
    perCell->addPerDimer(perDimer);
    perDimer->addPerCell(perCell);
}

#endif // SITEBASEDSIMULATION_CONTEXT_H

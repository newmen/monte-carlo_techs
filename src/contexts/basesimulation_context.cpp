#include <cmath>
#include <cstdlib>
#include "basesimulation_context.h"
#include "../roles/neighbouring_role.h"

BaseSimulationContext::BaseSimulationContext(AreaData *area, const BaseReactorContext *reactor) :
    _area(area), _reactor(reactor)
{
    _area->eachCell([this](int *const cell, int x, int y) {
        _cells.push_back(_reactor->createCell(cell, x ,y));
    });

    for (auto p = _cells.begin(); p != _cells.end(); ++p) {
        CellData *cell = *p;
        static_cast<NeighbouringRole<CellData> *>(cell)->uniqPairs(_area, [this, &cell](int neighbourIndex) {
            _dimers.push_back(_reactor->createDimer(cell, _cells[neighbourIndex]));
        });
    }
}

BaseSimulationContext::~BaseSimulationContext() {
    for (auto p = _dimers.begin(); p != _dimers.end(); ++p) delete *p;
    for (auto p = _cells.begin(); p != _cells.end(); ++p) delete *p;
}

template <>
void BaseSimulationContext::reinitSite<CellData>(CellData *cell) const {
    _reactor->reinitCell(cell, _area);
}

template <>
void BaseSimulationContext::reinitSite<DimerData>(DimerData *dimer) const {
    _reactor->reinitDimer(dimer, _area);
}

void BaseSimulationContext::eachCell(std::function<void (CellData *const)> lambda) const {
    eachSite(_cells, lambda);
}

void BaseSimulationContext::eachDimer(std::function<void (DimerData *const)> lambda) const {
    eachSite(_dimers, lambda);
}

void BaseSimulationContext::eachCellReaction(std::function<void (const ReactionData<CellData> *const)> lambda) const {
    _reactor->eachReaction(lambda);
}

void BaseSimulationContext::eachDimerReaction(std::function<void (const ReactionData<DimerData> *const)> lambda) const {
    _reactor->eachReaction(lambda);
}

long double BaseSimulationContext::randomN01() const {
    return (long double)rand() / RAND_MAX;
}

long double BaseSimulationContext::negativLogU() const {
    long double u;
    do u = randomN01(); while (u == 0.0);
    return -log(u);
}

template <class SData>
void BaseSimulationContext::eachSite(const std::vector<SData *> &sites, const std::function<void (SData *const)> &lambda) const {
    for (auto p = sites.cbegin(); p != sites.cend(); ++p) {
        reinitSite(*p);
        lambda(*p);
    }
}

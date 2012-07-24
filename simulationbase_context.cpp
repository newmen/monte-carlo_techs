#include <cmath>
#include <cstdlib>
#include "simulationbase_context.h"
#include "neighbouring_role.h"

SimulationBaseContext::SimulationBaseContext(AreaData *area, const ReactorBaseContext *reactor) :
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

SimulationBaseContext::~SimulationBaseContext() {
    for (auto p = _dimers.begin(); p != _dimers.end(); ++p) delete *p;
    for (auto p = _cells.begin(); p != _cells.end(); ++p) delete *p;
}

template <>
void SimulationBaseContext::reinitSite<CellData>(CellData *cell) const {
    _reactor->reinitCell(cell, _area);
}

template <>
void SimulationBaseContext::reinitSite<DimerData>(DimerData *dimer) const {
    _reactor->reinitDimer(dimer, _area);
}

void SimulationBaseContext::eachCell(std::function<void (CellData *const)> lambda) const {
    eachSite(_cells, lambda);
}

void SimulationBaseContext::eachDimer(std::function<void (DimerData *const)> lambda) const {
    eachSite(_dimers, lambda);
}

void SimulationBaseContext::eachCellReaction(std::function<void (const ReactionData<CellData> *const)> lambda) const {
    _reactor->eachReaction(lambda);
}

void SimulationBaseContext::eachDimerReaction(std::function<void (const ReactionData<DimerData> *const)> lambda) const {
    _reactor->eachReaction(lambda);
}

long double SimulationBaseContext::randomN01() const {
    return (long double)rand() / RAND_MAX;
}

long double SimulationBaseContext::negativLogU() const {
    long double u;
    do u = randomN01(); while (u == 0.0);
    return -log(u);
}

template <class SData>
void SimulationBaseContext::eachSite(const std::vector<SData *> &sites, const std::function<void (SData *const)> &lambda) const {
    for (auto p = sites.cbegin(); p != sites.cend(); ++p) {
        reinitSite(*p);
        lambda(*p);
    }
}

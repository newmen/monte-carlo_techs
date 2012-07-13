#include <cmath>
#include <cstdlib>
#include "simulationbase_context.h"
#include "neighbouring_role.h"

SimulationBaseContext::SimulationBaseContext(AreaData *area, const ReactorBaseData *reactor) :
    _area(area), _reactor(reactor)
{
    _area->eachCell([this](CellData *const cell) {
        static_cast<NeighbouringRole<CellData> *>(cell)->uniqPairs(_area, [this, &cell](CellData *const neighbour) {
            _dimers.push_back(new DimerData(cell, neighbour));
        });
    });
}

SimulationBaseContext::~SimulationBaseContext() {
    for (auto p = _dimers.begin(); p != _dimers.end(); ++p) delete *p;
}

void SimulationBaseContext::eachCell(std::function<void (CellData *const)> lambda) const {
    _area->eachCell(lambda);
}

void SimulationBaseContext::eachDimer(std::function<void (DimerData *const)> lambda) const {
    for (auto p = _dimers.cbegin(); p != _dimers.cend(); ++p) lambda(*p);
}

void SimulationBaseContext::eachCellReaction(std::function<void (const ReactionData<CellData> *const)> lambda) const {
    _reactor->eachReaction(lambda);
}

void SimulationBaseContext::eachDimerReaction(std::function<void (const ReactionData<DimerData> *const)> lambda) const {
    _reactor->eachReaction(lambda);
}

double SimulationBaseContext::randomN01() const {
    return (double)rand() / RAND_MAX;
}

double SimulationBaseContext::negativLogU() const {
    double u;
    do u = randomN01(); while (u == 0);
    return -log(u);
}

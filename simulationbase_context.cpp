#include <cmath>
#include <cstdlib>
#include "simulationbase_context.h"

#include <algorithm>
#include "neighbouring_role.h"

#include "reaction12_data.h"
#include "reaction21_data.h"
#include "reaction23_data.h"
#include "reaction31_data.h"
#include "reaction34_data.h"
#include "reaction35_data.h"
#include "reaction51_data.h"
#include "cellreacting_role.h"
#include "dimerreactioncapturing_role.h"
#include "dimerreactionexchanging_role.h"
#include "dimerreactionstabilizing_role.h"

SimulationBaseContext::SimulationBaseContext(AreaData *area) : _area(area) {
    initDimers();

    _cellReactions.push_back(new CellReactingRole<Reaction12Data>);
    _cellReactions.push_back(new CellReactingRole<Reaction21Data>);
    _cellReactions.push_back(new CellReactingRole<Reaction23Data>);

    _dimerReactions.push_back(new DimerReactionExchangingRole<Reaction31Data>);
    _dimerReactions.push_back(new DimerReactionStabilizingRole<Reaction34Data>);
    _cellReactions.push_back(new CellReactingRole<Reaction35Data>);
    _dimerReactions.push_back(new DimerReactionCapturingRole<Reaction51Data>);

//    _dimerReactions.push_back(new DimerReactionExchangingRole<Reaction31Data>);
//    _cellReactions.push_back(new CellReactingRole<Reaction34Data>);
//    _cellReactions.push_back(new CellReactingRole<Reaction35Data>);
//    _cellReactions.push_back(new CellReactingRole<Reaction51Data>);
}

SimulationBaseContext::~SimulationBaseContext() {
    for (auto p = _cellReactions.begin(); p != _cellReactions.end(); ++p) delete *p;
    for (auto p = _dimerReactions.begin(); p != _dimerReactions.end(); ++p) delete *p;

    for (auto p = _dimers.begin(); p != _dimers.end(); ++p) delete *p;
}

void SimulationBaseContext::eachCell(std::function<void (CellData *const)> lambda) const {
    _area->eachCell(lambda);
}

void SimulationBaseContext::eachDimer(std::function<void (DimerData *const)> lambda) const {
    for_each(_dimers.begin(), _dimers.end(), lambda);
}

void SimulationBaseContext::eachCellReaction(std::function<void (const CellReaction *const)> lambda) const {
    for_each(_cellReactions.cbegin(), _cellReactions.cend(), lambda);
}

void SimulationBaseContext::eachDimerReaction(std::function<void (const DimerReaction *const)> lambda) const {
    for_each(_dimerReactions.cbegin(), _dimerReactions.cend(), lambda);
}

double SimulationBaseContext::randomN01() const {
    return (double)rand() / RAND_MAX;
}

double SimulationBaseContext::negativLogU() const {
    double u;
    do u = randomN01(); while (u == 0);
    return -log(u);
}

void SimulationBaseContext::initDimers() {
    _area->eachCell([this](CellData *const cell) {
        static_cast<NeighbouringRole<CellData> *>(cell)->uniqPairs(_area, [this, &cell](CellData *const neighbour) {
            _dimers.push_back(new DimerData(cell, neighbour));
        });
    });
}

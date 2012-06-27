#include <cmath>
#include <cstdlib>
#include "simulationbase_context.h"
#include "site_data.h"
#include "simulating_role.h"

#include "reaction12_data.h"
#include "reaction21_data.h"
#include "reaction23_data.h"
#include "reaction31_data.h"
#include "reaction34_data.h"
#include "reaction35_data.h"
#include "reaction51mr_data.h"

#include "reacting_role.h"
#include "reactionmigrating_role.h"
#include "reactiondissolutionmigrating_role.h"
#include "stabilizationreacting_role.h"

SimulationBaseContext::SimulationBaseContext(AreaData *area) : _area(area) {
    _reactions.push_back(new ReactingRole<Reaction12Data>);
    _reactions.push_back(new ReactingRole<Reaction21Data>);
    _reactions.push_back(new ReactingRole<Reaction23Data>);

//    _reactions.push_back(new ReactionMigratingRole<Reaction31Data>);
//    _reactions.push_back(new StabilizationReactingRole<Reaction34Data>);
//    _reactions.push_back(new ReactingRole<Reaction35Data>);
//    _reactions.push_back(new ReactionDissolutionMigratingRole<Reaction51MRData, 5>);

    _reactions.push_back(new ReactionMigratingRole<Reaction31Data>);
    _reactions.push_back(new ReactingRole<Reaction34Data>);
    _reactions.push_back(new ReactingRole<Reaction35Data>);
    _reactions.push_back(new ReactingRole<Reaction51MRData>);
}

SimulationBaseContext::~SimulationBaseContext() {
    for (auto p = _reactions.begin(); p != _reactions.end(); ++p) delete *p;
}

void SimulationBaseContext::throughArea(std::function<void (int *, int **)> lambda) const {
    static_cast<SimulatingRole<AreaData> *>(_area)->cellsWithNeighsIter(lambda);
}

int SimulationBaseContext::reactionsNum() const {
    return (int)(_reactions.size());
}

void SimulationBaseContext::eachReaction(std::function<void (IReactingRole *const)> lambda) const {
    for (auto p = _reactions.cbegin(); p != _reactions.cend(); ++p) lambda(*p);
}

IReactingRole *SimulationBaseContext::reaction(int index) const {
    return _reactions[index];
}

double SimulationBaseContext::randomN01() const {
    return (double)rand() / RAND_MAX;
}

double SimulationBaseContext::negativLogU() const {
    double u;
    do u = randomN01(); while (u == 0);
    return -log(u);
}

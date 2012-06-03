#include <cstdlib>
#include "simulationbase_context.h"
#include "site_data.h"
#include "simulating_role.h"

#include "reaction12_data.h"
#include "reaction21_data.h"
#include "reaction23_data.h"
#include "reaction3113m_data.h"
#include "reaction34ms_data.h"
#include "reaction35_data.h"
#include "reaction51mr_data.h"

#include "reacting_role.h"
#include "reactionmigrating_role.h"
#include "reactiondissolutionmigrating_role.h"
#include "stabilizationreacting_role.h"

SimulationBaseContext::SimulationBaseContext(AreaData *area) : _area(area) {
    _reactions[0] = new ReactingRole<Reaction12Data>;
    _reactions[1] = new ReactingRole<Reaction21Data>;
    _reactions[2] = new ReactingRole<Reaction23Data>;
    _reactions[3] = new ReactionMigratingRole<Reaction3113MData>;
    _reactions[4] = new StabilizationReactingRole<Reaction34MSData>;
    _reactions[5] = new ReactingRole<Reaction35Data>;
    _reactions[6] = new ReactionDissolutionMigratingRole<Reaction51MRData, 5>;
}

SimulationBaseContext::~SimulationBaseContext() {
    for (auto reaction : _reactions) delete reaction;
}

void SimulationBaseContext::throughArea(std::function<void (int *, int **)> lambda) const {
    static_cast<SimulatingRole<AreaData> *>(_area)->cellsWithNeighsIter(lambda);
}

IReactingRole *SimulationBaseContext::reaction(int index) const {
    return _reactions[index];
}

float SimulationBaseContext::randomN01() const {
    return (float)rand() / RAND_MAX;
}

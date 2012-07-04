#include <cmath>
#include <cstdlib>
#include "simulationbase_context.h"

#include <algorithm>
#include "simulating_role.h"
#include "siteneighbouring_role.h"
#include "dimerneighbouring_role.h"

#include "reaction12_data.h"
#include "reaction21_data.h"
#include "reaction23_data.h"
#include "reaction31_data.h"
#include "reaction34_data.h"
#include "reaction35_data.h"
#include "reaction51_data.h"
#include "sitereacting_role.h"
#include "dimerreactioncapturing_role.h"
#include "dimerreactionexchanging_role.h"
#include "dimerreactionstabilizing_role.h"

SimulationBaseContext::SimulationBaseContext(AreaData *area) : _area(area) {
    _siteReactions.push_back(new SiteReactingRole<Reaction12Data>);
    _siteReactions.push_back(new SiteReactingRole<Reaction21Data>);
    _siteReactions.push_back(new SiteReactingRole<Reaction23Data>);

    _dimerReactions.push_back(new DimerReactionExchangingRole<Reaction31Data>);
    _dimerReactions.push_back(new DimerReactionStabilizingRole<Reaction34Data>);
    _siteReactions.push_back(new SiteReactingRole<Reaction35Data>);
    _dimerReactions.push_back(new DimerReactionCapturingRole<Reaction51Data>);

//    _dimerReactions.push_back(new DimerReactionExchangingRole<Reaction31Data>);
//    _siteReactions.push_back(new SiteReactingRole<Reaction34Data>);
//    _siteReactions.push_back(new SiteReactingRole<Reaction35Data>);
//    _siteReactions.push_back(new SiteReactingRole<Reaction51Data>);
}

SimulationBaseContext::~SimulationBaseContext() {
    for (auto p = _siteReactions.begin(); p != _siteReactions.end(); ++p) delete *p;
    for (auto p = _dimerReactions.begin(); p != _dimerReactions.end(); ++p) delete *p;
}

int SimulationBaseContext::siteReactionsNum() const {
    return (int)(_siteReactions.size());
}

int SimulationBaseContext::dimerReactionsNum() const {
    return (int)(_dimerReactions.size());
}

void SimulationBaseContext::reviewAllEvents() {
    static_cast<SimulatingRole<AreaData> *>(_area)->eachSite([this](const SharedSite &site) {
        this->estimateEachReactionForSite(site);

        if (this->dimerReactionsNum() > 0) {
            this->eachSiteNeighbour(*site, [this, &site](const SharedSite &neighbour) {
                SharedDimer dimer(new DimerData(site, neighbour));
                this->estimateEachReactionForDimer(dimer);
            });
        }
    });
}

void SimulationBaseContext::eachSiteReaction(std::function<void (const SiteReaction *const)> lambda) const {
    for_each(_siteReactions.cbegin(), _siteReactions.cend(), lambda);
}

void SimulationBaseContext::eachSiteNeighbour(const SiteData &site, std::function<void (const SharedSite &)> lambda) const {
    static_cast<const SiteNeighbouringRole<SiteData> *>(&site)->eachNeighbour(_area, lambda);
}

void SimulationBaseContext::eachDimerReaction(std::function<void (const DimerReaction *const)> lambda) const {
    for_each(_dimerReactions.cbegin(), _dimerReactions.cend(), lambda);
}

void SimulationBaseContext::eachDimerNeighbour(const DimerData &dimer, std::function<void (const SharedSite &)> lambda) const {
    static_cast<const DimerNeighbouringRole<DimerData> *>(&dimer)->eachNeighbour(_area, lambda);
}

double SimulationBaseContext::randomN01() const {
    return (double)rand() / RAND_MAX;
}

double SimulationBaseContext::negativLogU() const {
    double u;
    do u = randomN01(); while (u == 0);
    return -log(u);
}

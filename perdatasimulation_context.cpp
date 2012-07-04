#include "perdatasimulation_context.h"

PerDataSimulationContext::PerDataSimulationContext(AreaData *area) :
    SimulationBaseContext(area) {}

void PerDataSimulationContext::estimateEachReactionForSite(const SharedSite &site) {
    PerSite *perSite = createData(site);
    addRates(perSite);
    _cellsToPerSites[site->cellPtr()] = perSite;
    store(perSite);
}

void PerDataSimulationContext::estimateEachReactionForDimer(const SharedDimer &dimer) {
    PerDimer *perDimer = createData(dimer);
    addRates(perDimer);
    _cellsToPerDimers[dimer->first().cellPtr()].push_back(perDimer);
    _cellsToPerDimers[dimer->second().cellPtr()].push_back(perDimer);
    store(perDimer);
}

void PerDataSimulationContext::updateNeighbours(PerSite *perSite) {
    const SiteData &site = perSite->siteOrDimer();
    eachSiteNeighbour(site, updateNeighboursRatesLambda());

    updateAssociatedDimersRates(site.cellPtr());
}

void PerDataSimulationContext::updateNeighbours(PerDimer *perDimer) {
    const DimerData &dimer = perDimer->siteOrDimer();
    eachDimerNeighbour(dimer, updateNeighboursRatesLambda());

    PerDimerCache perDimerCache;
    perDimerCache.insert(perDimer);
    updateAssociatedDimersRates(dimer.first().cellPtr(), &perDimerCache);
    updateAssociatedDimersRates(dimer.second().cellPtr(), &perDimerCache);
}

std::function<void (const SharedSite &)> PerDataSimulationContext::updateNeighboursRatesLambda() const {
    return [this](const SharedSite &neighbour) {
        const int *cell = neighbour->cellPtr();
        _cellsToPerSites.find(cell)->second->updateRates();
    };
}

void PerDataSimulationContext::addRates(PerSite *perSite) const {
    eachSiteReaction([&perSite](const SiteReaction *const reaction) {
        perSite->addRate(reaction);
    });
}

void PerDataSimulationContext::addRates(PerDimer *perDimer) const {
    eachDimerReaction([&perDimer](const DimerReaction *const reaction) {
        perDimer->addRate(reaction);
    });
}

void PerDataSimulationContext::updateAssociatedDimersRates(const int *cell, PerDimerCache *perDimerCache) {
    auto perDimers = _cellsToPerDimers[cell];
    for (auto p = perDimers.begin(); p != perDimers.end(); ++p) {
        if (perDimerCache != 0) {
            if (perDimerCache->find(*p) != perDimerCache->end()) continue;
            else perDimerCache->insert(*p);
        }
        (*p)->updateRates();
    }
}

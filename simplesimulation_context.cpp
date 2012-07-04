#include "simplesimulation_context.h"

SimpleSimulationContext::SimpleSimulationContext(AreaData *area) :
    SimulationBaseContext(area) {}

void SimpleSimulationContext::reviewAllEvents() {
    clearAllEvents();
    SimulationBaseContext::reviewAllEvents();
}

void SimpleSimulationContext::estimateEachReactionForSite(const SharedSite &site) {
    eachSiteReaction([this, &site](const SiteReaction *const siteReaction) {
        addSiteEvent(site, siteReaction);
    });
}

void SimpleSimulationContext::estimateEachReactionForDimer(const SharedDimer &dimer) {
    eachDimerReaction([this, &dimer](const DimerReaction *const dimerReaction) {
        addDimerEvent(dimer, dimerReaction);
    });
}



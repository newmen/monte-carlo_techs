#include "simplesimulation_context.h"

SimpleSimulationContext::SimpleSimulationContext(AreaData *area, const BaseReactorContext *reactor) :
    BaseSimulationContext(area, reactor) {}

void SimpleSimulationContext::reviewAllEvents() {
    clearAllEvents();

    int n = 0;
    eachDimer([this, &n](DimerData *const dimer) {
        if (n++ % 2 == 0) {
            CellData *const cell = dimer->first;
            reinitSite(cell);
            this->eachCellReaction([this, &cell](const ReactionData<CellData> *const reaction) {
                addCellEvent(cell, reaction);
            });
        }

        this->eachDimerReaction([this, &dimer](const ReactionData<DimerData> *const reaction) {
            addDimerEvent(dimer, reaction);
        });
    });
}

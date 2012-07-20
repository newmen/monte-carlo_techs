#include "simplesimulation_context.h"

SimpleSimulationContext::SimpleSimulationContext(AreaData *area, const ReactorBaseContext *reactor) :
    SimulationBaseContext(area, reactor) {}

void SimpleSimulationContext::reviewAllEvents() {
    clearAllEvents();

    eachCell([this](CellData *const cell) {
        this->eachCellReaction([this, &cell](const ReactionData<CellData> *const reaction) {
            addCellEvent(cell, reaction);
        });
    });

    eachDimer([this](DimerData *const dimer) {
        this->eachDimerReaction([this, &dimer](const ReactionData<DimerData> *const reaction) {
            addDimerEvent(dimer, reaction);
        });
    });
}

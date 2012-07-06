#include "simplesimulation_context.h"

SimpleSimulationContext::SimpleSimulationContext(AreaData *area) :
    SimulationBaseContext(area) {}

void SimpleSimulationContext::reviewAllEvents() {
    clearAllEvents();

    eachCell([this](CellData *const cell) {
        this->eachCellReaction([this, &cell](const CellReaction *const reaction) {
            addCellEvent(cell, reaction);
        });
    });

    eachDimer([this](DimerData *const dimer) {
        this->eachDimerReaction([this, &dimer](const DimerReaction *const reaction) {
            addDimerEvent(dimer, reaction);
        });
    });
}

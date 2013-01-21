#include "optimizedsimplesimulation_context.h"

OptimizedSimpleSimulationContext::OptimizedSimpleSimulationContext(AreaData *area, const BaseReactorContext *reactor) :
    BaseSimulationContext(area, reactor) {}

OptimizedSimpleSimulationContext::~OptimizedSimpleSimulationContext() {
    for (auto p : _cellsToDimers) delete [] p.second;
}

void OptimizedSimpleSimulationContext::reviewAllEvents() {
    eachCell([this](CellData *const cell) {
        this->eachCellReaction([this, &cell](const ReactionData<CellData> *const reaction) {
            this->addCellEvent(cell, reaction);
        });
    });

    eachDimer([this](DimerData *const dimer) {
        this->eachDimerReaction([this, &dimer](const ReactionData<DimerData> *const reaction) {
            this->addDimerEvent(dimer, reaction);
        });

        bindCellDimer(dimer->first, dimer);
        bindCellDimer(dimer->second, dimer);
    });
}

void OptimizedSimpleSimulationContext::doAround(CellData *cell, const std::function<void (CellData *)> &cellLambda, const std::function<void (DimerData *)> &dimerLambda, int delph, int woDimerIndex) {
    cellLambda(cell);

    for (int i = 0; i < DIMERS_PER_CELL; ++i) {
        DimerData *dimer = _cellsToDimers[cell][i];
        if (dimer == 0) continue;

        if (delph == 0) {
            if (i != woDimerIndex) dimerLambda(dimer);
        } else {
            CellData *neighbourCell = (dimer->first == cell) ? dimer->second : dimer->first;
            doAround(neighbourCell, cellLambda, dimerLambda, delph - 1, woDimerIndex);
        }
    }
}

//////////// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1!
//////////// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1!
void OptimizedSimpleSimulationContext::doAround(DimerData *dimer, const std::function<void (CellData *)> &cellLambda, const std::function<void (DimerData *)> &dimerLambda) {
    dimerLambda(dimer);

    auto doWithCell = [this, &dimer, &cellLambda, &dimerLambda](CellData *cell, int woDimerIndex) {
        cellLambda(cell);

        int othersideWoDimerIndex;
        if (woDimerIndex == -1) othersideWoDimerIndex = -1;
        else if (woDimerIndex == 0) othersideWoDimerIndex = 2;
        else if (woDimerIndex == 3) othersideWoDimerIndex = 1;

        DimerData **dimersArr = _cellsToDimers[cell];
        for (int i = 0; i < DIMERS_PER_CELL; ++i) {
            DimerData *bondedDimer = dimersArr[i];
            if (bondedDimer == 0 || bondedDimer == dimer) continue;

            CellData *neighbourCell = (bondedDimer->first == cell) ? bondedDimer->second : bondedDimer->first;
            int updatedWoDimerIndex;
            if (i == othersideWoDimerIndex) updatedWoDimerIndex = -1;
            else updatedWoDimerIndex = woDimerIndex;
            doAround(neighbourCell, cellLambda, dimerLambda, 0, updatedWoDimerIndex);
        }
    };

    doWithCell(dimer->first, -1);
    doWithCell(dimer->second, (dimer->first->x() != dimer->second->x()) ? 3 : 0);

//    doAround(dimer->first, cellLambda, dimerLambda, 1);
//    doAround(dimer->second, cellLambda, dimerLambda, 1, (dimer->first->x() != dimer->second->x()) ? 3 : 2);
}
//////////// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1!
//////////// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1!

void OptimizedSimpleSimulationContext::bindCellDimer(CellData *cell, DimerData *dimer) {
    if (_cellsToDimers.find(cell) == _cellsToDimers.cend()) {
        _cellsToDimers[cell] = new DimerData *[DIMERS_PER_CELL];
        for (int i = 0; i < DIMERS_PER_CELL; ++i) _cellsToDimers[cell][i] = 0;
    }

    DimerData **dimersArr = _cellsToDimers[cell];
    // copypasted from percell_data.cpp
    int numOfDimers = 0;
    for (int i = 0; i < DIMERS_PER_CELL; ++i) {
        if (dimersArr[i] != 0) ++numOfDimers;
    }

    // this scope of conditions is depend from NeighbouringRole::uniqPairs method
    // and need for resolv correct perDimer other side index in updateRates method
    auto conditionsScope = [&dimersArr, &cell, &dimer](int i0, int i1, int i2, int i3) {
        if (cell->y() == 0 && cell->x() == 0) dimersArr[i0] = dimer;
        else if (cell->y() == 0 && cell->x() > 0) dimersArr[i1] = dimer;
        else if (cell->y() > 0 && cell->x() == 0) dimersArr[i2] = dimer;
        else /*if (cell->y() > 0 && cell->x() > 0)*/ dimersArr[i3] = dimer;
    };

    switch (numOfDimers) {
    case 0:
        conditionsScope(1, 3, 0, 0);
        break;
    case 1:
        conditionsScope(2, 1, 1, 3);
        break;
    case 2:
        conditionsScope(3, 2, 2, 1);
        break;
    case 3:
        conditionsScope(0, 0, 3, 2);
        break;
    }
}


#include <QVBoxLayout>
#include "mainwindow_context.h"

#include "../abcdcellreactor_context.h"
#include "../abcddimerreactor_context.h"
#include "../nocoreactor_context.h"

#include "../rejectionsimulation_context.h"
#include "../rejectionfreesimulation_context.h"
#include "../dynamicsimulation_context.h"
#include "../kineticsimulation_context.h"
#include "../treebasedsimulation_context.h"

MainWindowContext::MainWindowContext() : _area(5, 5), _cellSideLength(50) {
    setWindowTitle("Monte Carlo simulation");

//    _reactor = new ABCDCellReactorContext;
//    _reactor = new ABCDDimerReactorContext;
    _reactor = new NOCOReactorContext;

//    _simulationContext = new RejectionSimulationContext(&_area, _reactor);
//    _simulationContext = new RejectionFreeSimulationContext(&_area, _reactor);
//    _simulationContext = new DynamicSimulationContext(&_area, _reactor);
//    _simulationContext = new KineticSimulationContext(&_area, _reactor);
    _simulationContext = new TreeBasedSimulationContext(&_area, _reactor);
    _renderArea = new RenderAreaContext(&_area, _cellSideLength);

    _doButton = new QPushButton("Do reaction");
    connect(_doButton, SIGNAL(clicked()), this, SLOT(doReaction()));

    _playButton = new PlayButton("Play", "Stop");
    connect(_playButton, SIGNAL(timerStart()), this, SLOT(playAnimation()));
    connect(_playButton, SIGNAL(timerStop()), this, SLOT(stopAnimation()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(_renderArea);
    layout->addWidget(_doButton);
    layout->addWidget(_playButton);
    setLayout(layout);

    _animationTimer = new QTimer(this);
    connect(_animationTimer, SIGNAL(timeout()), this, SLOT(doReaction()));
}

MainWindowContext::~MainWindowContext() {
    delete _simulationContext;
    delete _reactor;
    delete _renderArea;
    delete _doButton;
    delete _playButton;
    delete _animationTimer;
}

void MainWindowContext::doReaction() {
    EventInfoData ei = _simulationContext->doReaction();

    if (ei.dt() == 0.0) {
        if (_playButton->started()) _playButton->click();
    } else if (ei.cell() != 0) {
        updateCell(ei.cell());
    } else {
        updateCell(ei.dimer()->first);
        updateCell(ei.dimer()->second);
    }
}

void MainWindowContext::playAnimation() {
    _animationTimer->start(5);
}

void MainWindowContext::stopAnimation() {
    _animationTimer->stop();
}

void MainWindowContext::updateCell(const CellData *cell) {
    _renderArea->update(cell->x() * _cellSideLength, cell->y() * _cellSideLength, _cellSideLength, _cellSideLength);
}

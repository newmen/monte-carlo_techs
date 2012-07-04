#include "mainwindow_context.h"
#include <QVBoxLayout>

#include "../rejectionsimulation_context.h"
#include "../rejectionfreesimulation_context.h"
#include "../dynamicsimulation_context.h"
#include "../kineticsimulation_context.h"
#include "../treebasedsimulation_context.h"

MainWindowContext::MainWindowContext() : _area(21, 13) {
    setWindowTitle("Monte Carlo simulation");

//    _simulationContext = new RejectionSimulationContext(&_area);
//    _simulationContext = new RejectionFreeSimulationContext(&_area);
//    _simulationContext = new DynamicSimulationContext(&_area);
//    _simulationContext = new KineticSimulationContext(&_area);
    _simulationContext = new TreeBasedSimulationContext(&_area);
    _renderArea = new RenderAreaContext(&_area, 15);

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
    delete _renderArea;
    delete _doButton;
    delete _playButton;
    delete _animationTimer;
}

void MainWindowContext::doReaction() {
    double dt = _simulationContext->doReaction();
    _renderArea->update();
    if (dt == 0.0) _playButton->click();
}

void MainWindowContext::playAnimation() {
    _animationTimer->start(25);
}

void MainWindowContext::stopAnimation() {
    _animationTimer->stop();
}

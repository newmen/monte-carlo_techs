#include "mainwindow_context.h"
#include <QVBoxLayout>

MainWindowContext::MainWindowContext() : _area(8, 5) {
    _simulationContext = new DynamicSimulationContext(&_area);
    _renderArea = new RenderAreaContext(&_area);

    _doButton = new QPushButton;
    _doButton->setText("Do reaction");

    connect(_doButton, SIGNAL(clicked()), this, SLOT(doReaction()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(_renderArea);
    layout->addWidget(_doButton);
    setLayout(layout);

    setWindowTitle("Monte Carlo simulation");
}

MainWindowContext::~MainWindowContext() {
    delete _simulationContext;
    delete _renderArea;
    delete _doButton;
}

void MainWindowContext::doReaction() {
    _simulationContext->doReaction();
    _renderArea->update();
}

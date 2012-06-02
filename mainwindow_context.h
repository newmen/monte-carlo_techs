#ifndef MAINWINDOW_CONTEXT_H
#define MAINWINDOW_CONTEXT_H

#include <QWidget>
#include <QPushButton>
#include "dynamicsimulation_context.h"
#include "renderarea_context.h"

class MainWindowContext : public QWidget
{
    Q_OBJECT
public:
    MainWindowContext();
    ~MainWindowContext();
    
//signals:
//public slots:
private slots:
    void doReaction();

private:
    AreaData _area;

    DynamicSimulationContext *_simulationContext;
    RenderAreaContext *_renderArea;

    QPushButton *_doButton;
};

#endif // MAINWINDOW_CONTEXT_H

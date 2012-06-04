#ifndef MAINWINDOW_CONTEXT_H
#define MAINWINDOW_CONTEXT_H

#include <QWidget>
#include <QPushButton>
#include <QTimer>
#include "playbutton.h"
#include "renderarea_context.h"

#include "dynamicsimulation_context.h"
#include "kineticsimulation_context.h"
#include "rejectionsimulation_context.h"

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

    void playAnimation();
    void stopAnimation();

private:
    AreaData _area;

//    DynamicSimulationContext *_simulationContext;
//    KineticSimulationContext *_simulationContext;
    RejectionSimulationContext *_simulationContext;
    RenderAreaContext *_renderArea;

    QPushButton *_doButton;
    PlayButton *_playButton;
    QTimer *_animationTimer;
};

#endif // MAINWINDOW_CONTEXT_H

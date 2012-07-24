#ifndef MAINWINDOW_CONTEXT_H
#define MAINWINDOW_CONTEXT_H

#include <QWidget>
#include <QPushButton>
#include <QStatusBar>
#include <QTimer>
#include "playbutton.h"
#include "renderarea_context.h"

#include "../reactorbase_context.h"
#include "../simulationbase_context.h"

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
    void updateCell(const CellData *cell);
    void updateStatusBar();

private:
    AreaData _area;
    ReactorBaseContext *_reactor;
    SimulationBaseContext *_simulationContext;
    RenderAreaContext *_renderArea;
    float _cellSideLength;

    long double _totalTime;

    QStatusBar *_statusBar;
    QPushButton *_doButton;
    PlayButton *_playButton;
    QTimer *_animationTimer;
};

#endif // MAINWINDOW_CONTEXT_H

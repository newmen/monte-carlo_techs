#ifndef RENDERAREA_CONTEXT_H
#define RENDERAREA_CONTEXT_H

#include <QWidget>
#include "../../src/datas/area_data.h"

class RenderAreaContext : public QWidget
{
    Q_OBJECT
public:
    RenderAreaContext(float cellSideLength);

    void resetArea(const AreaData *area);

protected:
    void paintEvent(QPaintEvent *event);
    
private:
    void processSize();

    const AreaData *_area;
    float _cellSideLength;
};

#endif // RENDERAREA_CONTEXT_H

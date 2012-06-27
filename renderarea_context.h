#ifndef RENDERAREA_CONTEXT_H
#define RENDERAREA_CONTEXT_H

#include <QWidget>
#include "area_data.h"

class RenderAreaContext : public QWidget
{
    Q_OBJECT
public:
    explicit RenderAreaContext(const AreaData *area, float cellSideLength);

protected:
    void paintEvent(QPaintEvent *);
    
private:
    const AreaData *_area;
    const float _cellSideLength;
};

#endif // RENDERAREA_CONTEXT_H

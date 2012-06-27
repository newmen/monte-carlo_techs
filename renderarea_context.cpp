#include <QtGui>
#include "renderarea_context.h"
#include "drawing_role.h"

RenderAreaContext::RenderAreaContext(const AreaData *area, float cellSideLength) :
    _area(area), _cellSideLength(cellSideLength)
{
    setMinimumSize(_cellSideLength * _area->sizeX(), _cellSideLength * _area->sizeY());
}

void RenderAreaContext::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    static_cast<const DrawingRole<AreaData> *>(_area)->draw(&painter, _cellSideLength);

    painter.setRenderHint(QPainter::Antialiasing, false);
}

#include <QtGui>
#include "renderarea_context.h"
#include "drawing_role.h"

RenderAreaContext::RenderAreaContext(float cellSideLength) : _cellSideLength(cellSideLength) {}

void RenderAreaContext::resetArea(const AreaData *area) {
    _area = area;
    processSize();
}

void RenderAreaContext::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPen pen(Qt::transparent);
    painter.setPen(pen);

    painter.setRenderHint(QPainter::Antialiasing, true);
    static_cast<const DrawingRole<AreaData> *>(_area)->draw(&painter, _cellSideLength);

    painter.setRenderHint(QPainter::Antialiasing, false);
}

void RenderAreaContext::processSize() {
    setMinimumSize(_cellSideLength * _area->sizeX(), _cellSideLength * _area->sizeY());
}

#include <QtGui>
#include "renderarea_context.h"
#include "drawing_role.h"

#define SIDE_LENGTH 15

RenderAreaContext::RenderAreaContext(const AreaData *area) : _area(area) {
    setMinimumSize(SIDE_LENGTH * _area->sizeX(), SIDE_LENGTH * _area->sizeY());
}

void RenderAreaContext::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    static_cast<const DrawingRole<AreaData, SIDE_LENGTH> *>(_area)->draw(&painter);

    painter.setRenderHint(QPainter::Antialiasing, false);
}

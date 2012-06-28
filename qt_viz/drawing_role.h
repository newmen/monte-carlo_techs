#ifndef DRAWING_ROLE_H
#define DRAWING_ROLE_H

#include <QPainter>

template <class AData>
class DrawingRole : public AData
{
public:
    DrawingRole() {}

    void draw(QPainter *painter, float cellSideLength) const;

private:
    QPointF offset(float cellSideLength, int x, int y) const;
};

template <class AData>
void DrawingRole<AData>::draw(QPainter *painter, float cellSideLength) const {
    QPen pen(Qt::black);
    painter->setPen(pen);

    QRect rect(0, 0, cellSideLength, cellSideLength);
    coordsIterator([this, &painter, &rect, cellSideLength](int x, int y) {
        painter->save();
        painter->translate(this->offset(cellSideLength, x, y));

        QColor color;
        switch (*this->cell(x, y)) {
        case 1:
            color.setRgb(248, 248, 248);
            break;
        case 2:
            color.setRgb(222, 22, 22);
            break;
        case 3:
            color.setRgb(24, 24, 146);
            break;
        case 4:
            color.setRgb(33, 33, 33);
            break;
        case 5:
            color.setRgb(25, 225, 25);
            break;
        }
        painter->setBrush(color);
        painter->drawRect(rect);

        painter->restore();
    });
}

template <class AData>
QPointF DrawingRole<AData>::offset(float cellSideLength, int x, int y) const {
    return QPointF(x * cellSideLength, y * cellSideLength);
}

#endif // DRAWING_ROLE_H

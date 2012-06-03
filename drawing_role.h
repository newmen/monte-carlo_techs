#ifndef DRAWING_ROLE_H
#define DRAWING_ROLE_H

#include <QPainter>

template <class AData, int cellSideLength>
class DrawingRole : public AData
{
public:
    DrawingRole() {}

    void draw(QPainter *painter) const;

private:
    QPointF offset(int x, int y) const;
};

template <class AData, int cellSideLength>
void DrawingRole<AData, cellSideLength>::draw(QPainter *painter) const {
    QPen pen(Qt::black);
    painter->setPen(pen);

    QRect rect(0, 0, cellSideLength, cellSideLength);
    coordsIterator([this, &painter, &rect](int x, int y) {
        painter->save();
        painter->translate(this->offset(x, y));

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
            color.setRgb(225, 125, 25);
            break;
        }
        painter->setBrush(color);
        painter->drawRect(rect);

        painter->restore();
    });
}

template <class AData, int cellSideLength>
QPointF DrawingRole<AData, cellSideLength>::offset(int x, int y) const {
    return QPointF(x * cellSideLength, y * cellSideLength);
}

#endif // DRAWING_ROLE_H

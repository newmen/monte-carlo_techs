#ifndef EVENTRECORD_DATA_H
#define EVENTRECORD_DATA_H

#include <iostream>
#include "eventinfo_data.h"
#include "cell_data.h"
#include "point2d.h"

class EventRecordData
{
    enum class SiteType : short int { NOTHING = 0, SINGLE = 1, HORIZONTAL = 2, VERTICAL = 3 };
public:
    EventRecordData();
    explicit EventRecordData(const EventInfoData &ei);
    EventRecordData(CellType *const cell, CoordType x, CoordType y);

    std::ostream &write(std::ostream &os) const;
    std::istream &read(std::istream &is);

    double dt() const { return _dt; }
    CoordType x() const { return _coord.x; }
    CoordType y() const { return _coord.y; }
    bool nothing() const { return _type == SiteType::NOTHING; }
    bool isCell() const { return _type == SiteType::SINGLE; }
    bool isHorizontalDimer() const { return _type == SiteType::HORIZONTAL; }
//    bool isVerticalDimer() const { return _type == SiteType::VERTICAL; }
    CellType first() const { return _first; }
    CellType second() const { return _second; }

private:
    double _dt;
    Point2D _coord;
    SiteType _type;
    CellType _first, _second;
};

std::ostream &operator << (std::ostream &os, const EventRecordData &eventRecord);
std::istream &operator >> (std::istream &is, EventRecordData &eventRecord);

#endif // EVENTRECORD_DATA_H

#ifndef EVENTRECORD_DATA_H
#define EVENTRECORD_DATA_H

#include <iostream>
#include "eventinfo_data.h"
#include "cell_data.h"

struct Point2D {
    CoordType x, y;
};

class EventRecordData
{
    enum class SiteType : short int { SINGLE = 1, HORIZONTAL = 2, VERTICAL = 3 };
public:
    explicit EventRecordData(const EventInfoData &ei);
    EventRecordData(CellType *const cell, CoordType x, CoordType y);

    std::ostream &write(std::ostream &os) const;
    std::istream &read(std::istream &is);

private:
    double _dt;
    Point2D _coord;
    SiteType _type;
    CellType _first, _second;
};

std::ostream &operator << (std::ostream &os, const EventRecordData &eventRecord);
std::istream &operator >> (std::istream &is, EventRecordData &eventRecord);

#endif // EVENTRECORD_DATA_H

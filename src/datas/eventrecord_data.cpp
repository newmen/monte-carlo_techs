#include "eventrecord_data.h"

EventRecordData::EventRecordData() : _dt(0), _type(SiteType::NOTHING) {}

EventRecordData::EventRecordData(const EventInfoData &ei) : _dt(ei.dt()), _type(SiteType::NOTHING) {
    if (ei.cell() != 0) {
        _coord.x = ei.cell()->x();
        _coord.y = ei.cell()->y();
        _type = SiteType::SINGLE;
        _first = ei.cell()->value();
    } else if (ei.dimer() != 0) {
        _coord.x = ei.dimer()->first->x();
        _coord.y = ei.dimer()->first->y();
        if (ei.dimer()->first->x() != ei.dimer()->second->x()) {
            _type = SiteType::HORIZONTAL;
        } else {
            _type = SiteType::VERTICAL;
        }
        _first = ei.dimer()->first->value();
        _second = ei.dimer()->second->value();
    }
}

EventRecordData::EventRecordData(CellType *const cell, CoordType x, CoordType y) :
    _dt(0), _type(SiteType::SINGLE), _first(*cell)
{
    _coord.x = x;
    _coord.y = y;
}

std::ostream &EventRecordData::write(std::ostream &os) const {
    os.write((const char *)&_dt, sizeof(_dt));
    os.write((const char *)&_coord, sizeof(_coord));
    const char c_type = (char)_type;
    os.write(&c_type, sizeof(c_type));
    if (_type == SiteType::SINGLE) {
        os.write((const char *)&_first, sizeof(_first));
    } else {
        os.write((const char *)&_first, sizeof(_first));
        os.write((const char *)&_second, sizeof(_second));
    }
    return os;
}

std::istream &EventRecordData::read(std::istream &is) {
    is.read((char *)&_dt, sizeof(_dt));
    is.read((char *)&_coord, sizeof(_coord));
    char c_type;
    is.read(&c_type, sizeof(c_type));
    _type = (SiteType)c_type;
    if (_type == SiteType::SINGLE) {
        is.read((char *)&_first, sizeof(_first));
    } else {
        is.read((char *)&_first, sizeof(_first));
        is.read((char *)&_second, sizeof(_second));
    }
    return is;
}

std::ostream &operator << (std::ostream &os, const EventRecordData &eventRecord) {
    return eventRecord.write(os);
}

std::istream &operator >> (std::istream &is, EventRecordData &eventRecord) {
    return eventRecord.read(is);
}

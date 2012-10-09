#include "area_data.h"

AreaData::AreaData(CoordType sizeX, CoordType sizeY) : _sizeX(sizeX), _sizeY(sizeY) {
    _cells = new CellType[size()];
//    int i = 0;
//    for (CoordType y = 0; y < _sizeY; ++y) {
//        for (CoordType x = 0; x < _sizeX; ++x) {
//            _cells[i++] = 0;
//        }
//    }
}

AreaData::~AreaData() {
    delete [] _cells;
}

void AreaData::init(BaseDistributionContext *distributor) {
    int i = 0;
    for (CoordType y = 0; y < _sizeY; ++y) {
        for (CoordType x = 0; x < _sizeX; ++x) {
            distributor->selectAppropriateConcs(_sizeX, _sizeY, x, y);
            _cells[i++] = distributor->value();
        }
    }
}

void AreaData::eachCell(const std::function<void (CellType *const, CoordType, CoordType)> &lambda) const {
    for (CoordType y = 0; y < _sizeY; ++y) {
        for (CoordType x = 0; x < _sizeX; ++x) {
            lambda(&_cells[index(x, y)], x, y);
        }
    }
}

void AreaData::setValue(CellType value, CoordType x, CoordType y) {
    _cells[index(x, y)] = value;
}

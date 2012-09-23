#include "area_data.h"
#include <cstdlib>

AreaData::AreaData(CoordType sizeX, CoordType sizeY) : _sizeX(sizeX), _sizeY(sizeY) {
    _cells = new CellType[size()];
    int i = 0;
    for (CoordType y = 0; y < _sizeY; ++y) {
        for (CoordType x = 0; x < _sizeX; ++x) {
            int value = (rand() % 10 < 8) ? 1 : ((rand() % 2 == 0) ? 2 : 3);
//            int value = (rand() % 10 < 7) ? 1 : ((rand() % 3 == 0) ? 2 : ((rand() % 2 == 0) ? 3 : 4));
//            int value = 1;
            _cells[i++] = value;
        }
    }
}

AreaData::~AreaData() {
    delete [] _cells;
}

void AreaData::eachCell(const std::function<void (CellType *const, CoordType, CoordType)> &lambda) const {
    for (CoordType y = 0; y < _sizeY; ++y) {
        for (CoordType x = 0; x < _sizeX; ++x) {
            lambda(&_cells[index(x, y)], x, y);
        }
    }
}

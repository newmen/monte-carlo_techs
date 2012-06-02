#include "area_data.h"
//#include <cstdlib>

AreaData::AreaData(int sizeX, int sizeY) : _sizeX(sizeX), _sizeY(sizeY) {
    int total = _sizeX * _sizeY;
    _cells = new int[total];
    for (int i = 0; i < total; i++) {
//        _cells[i] = rand() % 3 + 1;
        _cells[i] = 1;
    }
}

AreaData::~AreaData() {
    delete [] _cells;
}

int *AreaData::cell(int x, int y) const {
    return &_cells[y * _sizeX + x];
}

void AreaData::coordsIterator(std::function<void (int, int)> lambda) const {
    for (int y = 0; y < _sizeY; ++y) {
        for (int x = 0; x < _sizeX; ++x) {
            lambda(x, y);
        }
    }
}

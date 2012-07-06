#include "area_data.h"
//#include <cstdlib>

AreaData::AreaData(int sizeX, int sizeY) : _sizeX(sizeX), _sizeY(sizeY) {
    _cells = new CellData*[size()];
    int i = 0;
    for (int y = 0; y < _sizeY; ++y) {
        for (int x = 0; x < _sizeX; ++x) {
//        value = rand() % 3 + 1;
            _cells[i++] = new CellData(1, x, y);
        }
    }
}

AreaData::~AreaData() {
    for (int i = 0; i < size(); ++i) delete _cells[i];
    delete [] _cells;
}

void AreaData::eachCell(std::function<void (CellData *const)> lambda) const {
    for (int i = 0; i < size(); ++i) lambda(_cells[i]);
}

CellData *AreaData::cell(int x, int y) const {
    return _cells[y * _sizeX + x];
}

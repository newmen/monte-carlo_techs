#include "area_data.h"
#include <cstdlib>

AreaData::AreaData(int sizeX, int sizeY) : _sizeX(sizeX), _sizeY(sizeY) {
    _cells = new int[size()];
    int i = 0;
    for (int y = 0; y < _sizeY; ++y) {
        for (int x = 0; x < _sizeX; ++x) {
//            int value = (rand() % 10 < 8) ? 1 : ((rand() % 2 == 0) ? 2 : 3);

            float cx1, cx2;
            if (y < _sizeY / 2 && x < _sizeX / 2) {
                cx1 = 0.067;    cx2 = 0.223;
            } else if (y < _sizeY / 2 && x >= _sizeX / 2) {
                cx1 = 0.249;    cx2 = 0.504;
            } else if (y >= _sizeY / 2 && x >= _sizeX / 2) {
                cx1 = 0.533;    cx2 = 0.292;
            } else { // if (y >= _sizeY / 2 && x < _sizeX / 2)
                cx1 = 0.319;    cx2 = 0.104;
            }

            float r = (float)(rand() % 100) / 100;
            int value = 1; // empty value
            if (r < cx1) value = 2;
            else if (r < cx1 + cx2) value = 3;

//            int value = (rand() % 10 < 7) ? 1 : ((rand() % 3 == 0) ? 2 : ((rand() % 2 == 0) ? 3 : 4));
//            int value = 1;
            _cells[i++] = value;
        }
    }
}

AreaData::~AreaData() {
    delete [] _cells;
}

void AreaData::eachCell(const std::function<void (int *const, int, int)> &lambda) const {
    for (int y = 0; y < _sizeY; ++y) {
        for (int x = 0; x < _sizeX; ++x) {
            lambda(&_cells[index(x, y)], x, y);
        }
    }
}

//int *AreaData::cell(int x, int y) const {
//    return _cells[index(x, y)];
//}

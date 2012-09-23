#ifndef AREA_DATA_H
#define AREA_DATA_H

#include <functional>
#include "cell_data.h"

class AreaData
{
public:
    AreaData(CoordType sizeX, CoordType sizeY);
    ~AreaData();

    int size() const { return _sizeX * _sizeY; }
    int sizeX() const { return _sizeX; }
    int sizeY() const { return _sizeY; }

    int index(short int x, short int y) const { return y * _sizeX + x; }
    CellType value(int index) const { return _cells[index]; }
    void eachCell(const std::function<void (CellType *const, CoordType, CoordType)> &lambda) const;

private:
    int _sizeX, _sizeY;
    CellType *_cells;
};

#endif // AREA_DATA_H

#ifndef AREA_DATA_H
#define AREA_DATA_H

#include <functional>
#include "cell_data.h"

class AreaData
{
public:
    AreaData(int sizeX, int sizeY);
    ~AreaData();

    int size() const { return _sizeX * _sizeY; }
    int sizeX() const { return _sizeX; }
    int sizeY() const { return _sizeY; }

    void eachCell(const std::function<void (CellData *const)> &lambda) const;
    CellData *cell(int x, int y) const;

private:
    int _sizeX, _sizeY;
    CellData **_cells;
};

#endif // AREA_DATA_H

#ifndef AREA_DATA_H
#define AREA_DATA_H

#include <functional>
#include "cell_data.h"
#include "../contexts/basedistribution_context.h"

class AreaData
{
public:
    AreaData(CoordType sizeX, CoordType sizeY);
    ~AreaData();

    void init(BaseDistributionContext *distributor);

    int size() const { return _sizeX * _sizeY; }
    CoordType sizeX() const { return _sizeX; }
    CoordType sizeY() const { return _sizeY; }

    int index(CoordType x, CoordType y) const { return y * _sizeX + x; }
    CellType value(int index) const { return _cells[index]; }
    void eachCell(const std::function<void (CellType *const, CoordType, CoordType)> &lambda) const;

    void setValue(CellType value, CoordType x, CoordType y);

private:
    int _sizeX, _sizeY;
    CellType *_cells;
};

#endif // AREA_DATA_H

#ifndef AREA_DATA_H
#define AREA_DATA_H

#include <functional>

class AreaData
{
public:
    AreaData(int sizeX, int sizeY);
    ~AreaData();

    int size() const { return _sizeX * _sizeY; }
    int sizeX() const { return _sizeX; }
    int sizeY() const { return _sizeY; }

    int index(int x, int y) const { return y * _sizeX + x; }

    void eachCell(const std::function<void (int *const, int, int)> &lambda) const;
//    int *cell(int x, int y) const;

private:
    int _sizeX, _sizeY;
    int *_cells;
};

#endif // AREA_DATA_H

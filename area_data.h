#ifndef AREA_DATA_H
#define AREA_DATA_H

#include <functional>

class AreaData
{
public:
    AreaData(int sizeX, int sizeY);
    ~AreaData();

//    int size() const { return _sizeX * _sizeY; }
    int sizeX() const { return _sizeX; }
    int sizeY() const { return _sizeY; }

    Cell *cell(int x, int y) const;

protected:
    void coordsIterator(std::function<void (int, int)> lambda) const;

private:
    int _sizeX, _sizeY;
    Cell *_cells;
};

#endif // AREA_DATA_H

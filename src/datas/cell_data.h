#ifndef CELL_DATA_H
#define CELL_DATA_H

class CellData
{
public:
    CellData(int *cell, int x, int y) : _cell(cell), _x(x), _y(y) {}
    virtual ~CellData() {}

    int value() const { return *_cell; }
    void setValue(int value) { *_cell = value; }

    int x() const { return _x; }
    int y() const { return _y; }

private:
    int *_cell;
    int _x, _y;
};

#endif // CELL_DATA_H

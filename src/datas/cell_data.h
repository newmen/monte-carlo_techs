#ifndef CELL_DATA_H
#define CELL_DATA_H

typedef short int CellType;
typedef short int CoordType;

#pragma pack(push, 2)
class CellData
{
public:
    CellData(CellType *cell, CoordType x, CoordType y) : _cell(cell), _x(x), _y(y) {}
    virtual ~CellData() {}

    CellType value() const { return *_cell; }
    void setValue(CellType value) { *_cell = value; }

    CoordType x() const { return _x; }
    CoordType y() const { return _y; }

private:
    CellType *_cell;
    CoordType _x, _y;
};
#pragma pack(pop)

#endif // CELL_DATA_H

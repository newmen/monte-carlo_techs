#ifndef CELL_DATA_H
#define CELL_DATA_H

typedef int CellValueType;

class CellData
{
public:
    CellData(CellValueType value, int x, int y) : _value(value), _x(x), _y(y) {}

    int value() const { return _value; }
    void setValue(int value) { _value = value; }

    int x() const { return _x; }
    int y() const { return _y; }

private:
    CellValueType _value;
    int _x, _y;
};

#endif // CELL_DATA_H

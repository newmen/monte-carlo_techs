#ifndef SITE_DATA_H
#define SITE_DATA_H

#include <memory>

class SiteData
{
public:
    SiteData(int *cell, int x, int y) : _cell(cell), _x(x), _y(y) {}

    int x() const { return _x; }
    int y() const { return _y; }

    const int *cellPtr() const { return _cell; }
    int cell() const { return *_cell; }
    void setCell(int value) { *_cell = value; }

private:
    int *_cell;
    int _x, _y;
};

typedef std::shared_ptr<SiteData> SharedSite;

#endif // SITE_DATA_H

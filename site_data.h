#ifndef SITE_DATA_H
#define SITE_DATA_H

#include <functional>

#define NEIGHBOURS_NUM 4

class SiteData
{
public:
    SiteData(int *cell, int *neighbours[NEIGHBOURS_NUM]);
    SiteData(const SiteData &anotherSite);
    ~SiteData();

    int cell() const;
    void setCell(int value);

    void neighboursIterator(std::function<void (int *)> lambda) const;

private:
    void initNeighbours(int *neighbours[NEIGHBOURS_NUM]);

    int *_cell;
    int **_neighbours;
};

#endif // SITE_DATA_H

#include "site_data.h"

SiteData::SiteData(int *cell, int *neighbours[]) : _cell(cell) {
    initNeighbours(neighbours);
}

SiteData::SiteData(const SiteData &anotherSite) : _cell(anotherSite._cell) {
    initNeighbours(anotherSite._neighbours);
}

SiteData::~SiteData() {
    delete [] _neighbours;
}

int SiteData::cell() const {
    return *_cell;
}

void SiteData::setCell(int value) {
    *_cell = value;
}

void SiteData::neighboursIterator(std::function<void (int *)> lambda) const {
    for (int i = 0; i < NEIGHBOURS_NUM; ++i) lambda(_neighbours[i]);
}

void SiteData::initNeighbours(int *neighbours[]) {
    _neighbours = new int *[NEIGHBOURS_NUM];
    for (int i = 0; i < NEIGHBOURS_NUM; ++i) _neighbours[i] = neighbours[i];
}

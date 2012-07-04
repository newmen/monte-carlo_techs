#include "ineighbouring_role.h"

void INeighbouringRole::neighboursIter(int (*neighboursCoords)[2], int neighboursNum,
                                           const AreaData *area, std::function<void (const SharedSite &)> lambda) const
{
    for (int i = 0; i < neighboursNum; ++i) {
        int *nc = neighboursCoords[i];
        checkAndUpdateIfNeed(nc, area);
        lambda(SharedSite(new SiteData(area->cell(nc[0], nc[1]), nc[0], nc[1])));
    }
}

void INeighbouringRole::checkAndUpdateIfNeed(int coords[2], const AreaData *area) const {
    coords[0] = torus(coords[0], area->sizeX());
    coords[1] = torus(coords[1], area->sizeY());
}

int INeighbouringRole::torus(int curr, int maxSize) const {
    if (curr < 0) return curr + maxSize;
    else if (curr >= maxSize) return curr - maxSize;
    else return curr;
}

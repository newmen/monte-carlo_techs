#ifndef INEIGHBOURING_ROLE_H
#define INEIGHBOURING_ROLE_H

#include <functional>
#include "area_data.h"
#include "site_data.h"

class INeighbouringRole
{
protected:
    void neighboursIter(int (*neighboursCoords)[2], int neighboursNum, const AreaData *area, std::function<void (const SharedSite &)> lambda) const;

private:
    void checkAndUpdateIfNeed(int coords[2], const AreaData *area) const;
    int torus(int curr, int maxSize) const;
};

#endif // INEIGHBOURING_ROLE_H

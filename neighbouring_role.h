#ifndef NEIGHBOURING_ROLE_H
#define NEIGHBOURING_ROLE_H

#include <functional>
#include "area_data.h"
#include "cell_data.h"
#include "dimer_data.h"

template <class SData>
class NeighbouringRole : public SData
{
public:
    template <typename Lambda>
    void eachNeighbour(const AreaData *area, const Lambda &lambda) const;

    template <typename Lambda>
    void uniqPairs(const AreaData *area, const Lambda &lambda) const;

private:
    void neighboursIter(int (*neighboursCoords)[2], int neighboursNum, const AreaData *area, std::function<void (CellData *const)> lambda) const;

    void checkAndUpdateIfNeed(int coords[2], const AreaData *area) const;
    int torus(int curr, int maxSize) const;
};

template <>
template <typename Lambda>
void NeighbouringRole<CellData>::uniqPairs(const AreaData *area, const Lambda &lambda) const {
    int neighboursCoords[][2] = {
        { this->x(), this->y() - 1 },
        { this->x() + 1, this->y() }
    };

    neighboursIter(neighboursCoords, 2, area, lambda);
}

template <>
template <typename Lambda>
void NeighbouringRole<CellData>::eachNeighbour(const AreaData *area, const Lambda &lambda) const {
    // the first pair of coordinates is the same as in uniqPairs method
    int neighboursCoords[][2] = {
        { this->x(), this->y() - 1 },
        { this->x() + 1, this->y() },
        { this->x(), this->y() + 1 },
        { this->x() - 1, this->y() }
    };

    neighboursIter(neighboursCoords, 4, area, lambda);
}

template <>
template <typename Lambda>
void NeighbouringRole<DimerData>::eachNeighbour(const AreaData *area, const Lambda &lambda) const {
    int ncs[6][2];
    if (this->first->x() == this->second->x()) {
        ncs[0][0] = this->first->x() - 1; ncs[0][1] = this->first->y();
        ncs[1][0] = this->first->x() + 1; ncs[1][1] = this->first->y();
        ncs[2][0] = this->second->x() - 1; ncs[2][1] = this->second->y();
        ncs[3][0] = this->second->x() + 1; ncs[3][1] = this->second->y();

        ncs[4][0] = this->first->x();
        ncs[5][0] = this->first->x();
        if (this->first->y() > this->second->y()) {
            ncs[4][1] = this->first->y() + 1;
            ncs[5][1] = this->second->y() - 1;
        } else {
            ncs[4][1] = this->first->y() - 1;
            ncs[5][1] = this->second->y() + 1;
        }
    } else {
        ncs[0][0] = this->first->x(); ncs[0][1] = this->first->y() - 1;
        ncs[1][0] = this->first->x(); ncs[1][1] = this->first->y() + 1;
        ncs[2][0] = this->second->x(); ncs[2][1] = this->second->y() - 1;
        ncs[3][0] = this->second->x(); ncs[3][1] = this->second->y() + 1;

        ncs[4][1] = this->first->y();
        ncs[5][1] = this->first->y();
        if (this->first->x() > this->second->x()) {
            ncs[4][0] = this->first->x() + 1;
            ncs[5][0] = this->second->x() - 1;
        } else {
            ncs[4][0] = this->first->x() - 1;
            ncs[5][0] = this->second->x() + 1;
        }
    }

    neighboursIter(ncs, 6, area, lambda);
}

template <class SData>
void NeighbouringRole<SData>::neighboursIter(int (*neighboursCoords)[2], int neighboursNum,
                                             const AreaData *area, std::function<void (CellData *const)> lambda) const
{
    for (int i = 0; i < neighboursNum; ++i) {
        int *nc = neighboursCoords[i];
        checkAndUpdateIfNeed(nc, area);
        lambda(area->cell(nc[0], nc[1]));
    }
}

template <class SData>
void NeighbouringRole<SData>::checkAndUpdateIfNeed(int coords[2], const AreaData *area) const {
    coords[0] = torus(coords[0], area->sizeX());
    coords[1] = torus(coords[1], area->sizeY());
}

template <class SData>
int NeighbouringRole<SData>::torus(int curr, int maxSize) const {
    if (curr < 0) return curr + maxSize;
    else if (curr >= maxSize) return curr - maxSize;
    else return curr;
}


#endif // NEIGHBOURING_ROLE_H

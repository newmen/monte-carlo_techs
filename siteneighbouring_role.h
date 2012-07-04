#ifndef SITENEIGHBOURING_ROLE_H
#define SITENEIGHBOURING_ROLE_H

#include "ineighbouring_role.h"

template <class SData>
class SiteNeighbouringRole :
        public INeighbouringRole,
        public SData
{
public:
    template <typename Lambda>
    void eachNeighbour(const AreaData *area, const Lambda &lambda) const;
};

template <class SData>
template <typename Lambda>
void SiteNeighbouringRole<SData>::eachNeighbour(const AreaData *area, const Lambda &lambda) const {
    int neighboursCoords[][2] = {
        { this->x(), this->y() - 1 },
        { this->x() + 1, this->y() },
        { this->x(), this->y() + 1 },
        { this->x() - 1, this->y() }
    };

    neighboursIter(neighboursCoords, 4, area, lambda);
}

#endif // SITENEIGHBOURING_ROLE_H

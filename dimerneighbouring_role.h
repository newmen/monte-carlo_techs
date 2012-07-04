#ifndef DIMERNEIGHBOURING_ROLE_H
#define DIMERNEIGHBOURING_ROLE_H

#include "ineighbouring_role.h"

template <class DData>
class DimerNeighbouringRole :
        public INeighbouringRole,
        public DData
{
public:
    template <typename Lambda>
    void eachNeighbour(const AreaData *area, const Lambda &lambda) const;
};

template <class DData>
template <typename Lambda>
void DimerNeighbouringRole<DData>::eachNeighbour(const AreaData *area, const Lambda &lambda) const {
    int ncs[6][2];
    if (this->first().x() == this->second().x()) {
        ncs[0][0] = this->first().x() - 1; ncs[0][1] = this->first().y();
        ncs[1][0] = this->first().x() + 1; ncs[1][1] = this->first().y();
        ncs[2][0] = this->second().x() - 1; ncs[2][1] = this->second().y();
        ncs[3][0] = this->second().x() + 1; ncs[3][1] = this->second().y();

        ncs[4][0] = this->first().x();
        ncs[5][0] = this->first().x();
        if (this->first().y() > this->second().y()) {
            ncs[4][1] = this->first().y() + 1;
            ncs[5][1] = this->second().y() - 1;
        } else {
            ncs[4][1] = this->first().y() - 1;
            ncs[5][1] = this->second().y() + 1;
        }
    } else {
        ncs[0][0] = this->first().x(); ncs[0][1] = this->first().y() - 1;
        ncs[1][0] = this->first().x(); ncs[1][1] = this->first().y() + 1;
        ncs[2][0] = this->second().x(); ncs[2][1] = this->second().y() - 1;
        ncs[3][0] = this->second().x(); ncs[3][1] = this->second().y() + 1;

        ncs[4][1] = this->first().y();
        ncs[5][1] = this->first().y();
        if (this->first().x() > this->second().x()) {
            ncs[4][0] = this->first().x() + 1;
            ncs[5][0] = this->second().x() - 1;
        } else {
            ncs[4][0] = this->first().x() - 1;
            ncs[5][0] = this->second().x() + 1;
        }
    }

    neighboursIter(ncs, 6, area, lambda);
}

#endif // DIMERNEIGHBOURING_ROLE_H

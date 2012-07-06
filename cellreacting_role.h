#ifndef CELLREACTING_ROLE_H
#define CELLREACTING_ROLE_H

#include "ireacting_role.h"
#include "cell_data.h"

template <class RData>
class CellReactingRole :
        public IReactingRole<CellData>,
        public virtual RData
{
public:
    double rate(const CellData &site) const;
    void doIt(CellData *const site) const;
};

template <class RData>
double CellReactingRole<RData>::rate(const CellData &site) const {
    return (site.value() == this->prevState()) ? this->k() : 0;
}

template <class RData>
void CellReactingRole<RData>::doIt(CellData *const site) const {
    site->setValue(this->nextState());
}

#endif // CELLREACTING_ROLE_H

#ifndef BASEDISTRIBUTION_CONTEXT_H
#define BASEDISTRIBUTION_CONTEXT_H

#include <cstdlib>
#include "../datas/cell_data.h"

class BaseDistributionContext
{
public:
    virtual ~BaseDistributionContext() {}

    // sizeX, sizeY, x, y
    virtual void selectAppropriateConcs(CoordType, CoordType, CoordType, CoordType) {}
    virtual int value() const {
        return 1;
    }
};

#endif // BASEDISTRIBUTION_CONTEXT_H

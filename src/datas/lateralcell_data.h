#ifndef LATERALCELL_DATA_H
#define LATERALCELL_DATA_H

#include "cell_data.h"
#include "lateralsite_data.h"

class LateralCellData :
        public CellData,
        public LateralSiteData
{
public:
    LateralCellData(CellType *cell, CoordType x, CoordType y, int numOfSpecs);
};

#endif // LATERALCELL_DATA_H

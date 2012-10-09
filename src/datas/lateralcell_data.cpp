#include "lateralcell_data.h"

LateralCellData::LateralCellData(CellType *cell, CoordType x, CoordType y, int numOfSpecs) :
    CellData(cell, x, y), LateralSiteData(numOfSpecs) {}


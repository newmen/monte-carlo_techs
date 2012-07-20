#include "lateralcell_data.h"

LateralCellData::LateralCellData(int *cell, int x, int y, int numOfSpecs) :
    CellData(cell, x, y), LateralSiteData(numOfSpecs) {}


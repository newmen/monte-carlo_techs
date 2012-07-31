#include "lateraldimer_data.h"

LateralDimerData::LateralDimerData(CellData *first, CellData *second, int numOfSpecs) :
    DimerData(first, second), LateralSiteData(numOfSpecs) {}



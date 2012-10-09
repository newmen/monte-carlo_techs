#include "lateraldimer_data.h"

LateralDimerData::LateralDimerData(CellData *first, CellData *second, short numOfSpecs) :
    DimerData(first, second), LateralSiteData(numOfSpecs) {}



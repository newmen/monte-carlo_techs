#ifndef LATERALDIMER_DATA_H
#define LATERALDIMER_DATA_H

#include "cell_data.h"
#include "dimer_data.h"
#include "lateralsite_data.h"

class LateralDimerData :
        public DimerData,
        public LateralSiteData
{
public:
    LateralDimerData(CellData *first, CellData *second, int numOfSpecs);
};

#endif // LATERALDIMER_DATA_H

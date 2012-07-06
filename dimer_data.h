#ifndef DIMER_DATA_H
#define DIMER_DATA_H

#include "cell_data.h"

struct DimerData
{
    CellData *const first;
    CellData *const second;

    DimerData(CellData *const first, CellData *const second) :
        first(first), second(second) {}
};

#endif // DIMER_DATA_H

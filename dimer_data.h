#ifndef DIMER_DATA_H
#define DIMER_DATA_H

#include "cell_data.h"

class DimerData
{
public:
    DimerData(CellData *const first, CellData *const second) : first(first), second(second) {}
    virtual ~DimerData() {}

public:
    CellData *const first;
    CellData *const second;
};

#endif // DIMER_DATA_H

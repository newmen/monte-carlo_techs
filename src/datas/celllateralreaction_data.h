#ifndef CELLLATERALREACTION_DATA_H
#define CELLLATERALREACTION_DATA_H

#include "cellreaction_data.h"
#include "lateralreaction_data.h"

class CellLateralReactionData :
        public CellReactionData,
        private LateralReactionData
{
public:
    CellLateralReactionData(int prevState, int nextState, long double k, long double Ea, long double epss[], const RTReactorContext *reactor);

protected:
    long double rateValue(const CellData *cell) const;
};

#endif // CELLLATERALREACTION_DATA_H

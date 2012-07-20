#ifndef CELLLATERALREACTION_DATA_H
#define CELLLATERALREACTION_DATA_H

#include "cellreaction_data.h"
#include "lateralreaction_data.h"

class CellLateralReactionData :
        public CellReactionData,
        private LateralReactionData
{
public:
    CellLateralReactionData(int prevState, int nextState, const RTReactorContext *reactor, double k, double Ea, double epss[], int numOfSpecs);

protected:
    double rateValue(const CellData *cell) const;
};

#endif // CELLLATERALREACTION_DATA_H

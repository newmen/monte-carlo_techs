#ifndef DIMERLATERALREACTIONEXPLOSION_DATA_H
#define DIMERLATERALREACTIONEXPLOSION_DATA_H

#include "dimerreactiondualstabilization_data.h"
#include "lateralreaction_data.h"

class DimerLateralReactionExplosionData :
        public DimerReactionDualStabilizationData,
        private LateralReactionData
{
public:
    DimerLateralReactionExplosionData(int firstPrevState, int secondPrevState, int nextState, const RTReactorContext *reactor, double k, double Ea, double epss[], int numOfSpecs);

protected:
    double rateValue(const DimerData *dimer) const;
};

#endif // DIMERLATERALREACTIONEXPLOSION_DATA_H

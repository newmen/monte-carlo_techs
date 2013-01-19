#ifndef DIMERREACTIONACTIVATIONEXPLOSION_DATA_H
#define DIMERREACTIONACTIVATIONEXPLOSION_DATA_H

#include "dimerreactiondualstabilization_data.h"
#include "reactionactivation_data.h"

class DimerReactionActivationExplosionData :
        public DimerReactionDualStabilizationData,
        public ReactionActivationData
{
public:
    DimerReactionActivationExplosionData(int firstPrevState, int secondPrevState, int nextState, long double k, long double Ea, const RTReactorContext *reactor);

protected:
    long double rateValue(const DimerData *dimer) const;
};

#endif // DIMERREACTIONACTIVATIONEXPLOSION_DATA_H

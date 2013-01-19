#ifndef DIMERLATERALREACTIONDISSOCIATION_DATA_H
#define DIMERLATERALREACTIONDISSOCIATION_DATA_H

#include "dimerreactiondissociation_data.h"
#include "lateralreaction_data.h"

class DimerLateralReactionDissociationData :
        public DimerReactionDissociationData,
        public LateralReactionData
{
public:
    DimerLateralReactionDissociationData(int emptyState, int dissociatedState, int separatedState, int remainingState, long double k, long double Ea, long double epss[], const RTReactorContext *reactor);

protected:
    long double rateValue(const DimerData *dimer) const;
};

#endif // DIMERLATERALREACTIONDISSOCIATION_DATA_H

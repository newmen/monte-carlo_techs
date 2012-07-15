#ifndef DIMERREACTIONSTABILIZATION_ROLE_H
#define DIMERREACTIONSTABILIZATION_ROLE_H

#include "reaction_data.h"
#include "dimer_data.h"

class DimerReactionStabilizationData : public ReactionData<DimerData>
{
public:
    DimerReactionStabilizationData(double rateValue, int prevState, int nextState);

    double rate(const DimerData *dimer) const;
    void doIt(DimerData *const dimer) const;
};

#endif // DIMERREACTIONSTABILIZATION_ROLE_H

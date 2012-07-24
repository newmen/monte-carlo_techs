#ifndef DIMERREACTIONSTABILIZATION_ROLE_H
#define DIMERREACTIONSTABILIZATION_ROLE_H

#include "reaction_data.h"
#include "dimer_data.h"

class DimerReactionStabilizationData : public ReactionData<DimerData>
{
public:
    DimerReactionStabilizationData(long double k, int prevState, int nextState);

    long double rate(const DimerData *dimer) const;
    void doIt(DimerData *const dimer) const;
};

#endif // DIMERREACTIONSTABILIZATION_ROLE_H

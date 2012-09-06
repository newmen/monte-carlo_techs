#ifndef DIMERREACTIONDUALSTABILIZATION_DATA_H
#define DIMERREACTIONDUALSTABILIZATION_DATA_H

#include "reaction_data.h"
#include "dimer_data.h"

class DimerReactionDualStabilizationData : public ReactionData<DimerData>
{
public:
    DimerReactionDualStabilizationData(int firstPrevState, int secondPrevState, int nextState, long double k);

    long double rate(const DimerData *dimer) const;
    void doIt(DimerData *const dimer) const;

private:
    int _secondPrevState;
};

#endif // DIMERREACTIONDUALSTABILIZATION_DATA_H

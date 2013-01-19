#ifndef DIMERREACTIONDISSOCIATION_DATA_H
#define DIMERREACTIONDISSOCIATION_DATA_H

#include "reaction_data.h"
#include "dimer_data.h"

class DimerReactionDissociationData : public ReactionData<DimerData>
{
public:
    DimerReactionDissociationData(int emptyState, int dissociatedState, int separatedState, int remainingState, long double k);

    long double rate(const DimerData *dimer) const;
    void doIt(DimerData *const dimer) const;

private:
    int _separatedState, _remainingState;
};

#endif // DIMERREACTIONDISSOCIATION_DATA_H

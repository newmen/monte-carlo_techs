#ifndef DIMERREACTIONEXCHANGING_ROLE_H
#define DIMERREACTIONEXCHANGING_ROLE_H

#include "reaction_data.h"
#include "dimer_data.h"

class DimerReactionExchangeData : public ReactionData<DimerData>
{
public:
    DimerReactionExchangeData(long double k, int prevState, int nextState);

    long double rate(const DimerData *dimer) const;
    void doIt(DimerData *const dimer) const;
};

#endif // DIMERREACTIONEXCHANGING_ROLE_H

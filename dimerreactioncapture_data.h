#ifndef DIMERREACTIONCAPTURING_ROLE_H
#define DIMERREACTIONCAPTURING_ROLE_H

#include "reaction_data.h"
#include "dimer_data.h"

class DimerReactionCaptureData : public ReactionData<DimerData>
{
public:
    DimerReactionCaptureData(long double k, int prevState, int nextState);

    long double rate(const DimerData *dimer) const;
    void doIt(DimerData *const dimer) const;
};

#endif // DIMERREACTIONCAPTURING_ROLE_H

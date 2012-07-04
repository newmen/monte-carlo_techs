#ifndef DIMERREACTIONCAPTURING_ROLE_H
#define DIMERREACTIONCAPTURING_ROLE_H

#include "ireacting_role.h"
#include "dimer_data.h"

template <class RData>
class DimerReactionCapturingRole :
        public IReactingRole<DimerData>,
        public RData
{
public:
    double rate(const DimerData &dimer) const;
    void doIt(DimerData *dimer) const;
};

template <class RData>
double DimerReactionCapturingRole<RData>::rate(const DimerData &dimer) const {
    return ((dimer.first().cell() == this->nextState() && dimer.second().cell() == this->prevState()) ||
            (dimer.first().cell() == this->prevState() && dimer.second().cell() == this->nextState())) ?
                this->k() : 0;
}

template <class RData>
void DimerReactionCapturingRole<RData>::doIt(DimerData *dimer) const {
    if (dimer->first().cell() == this->prevState()) {
        dimer->first().setCell(this->nextState());
    } else {
        dimer->second().setCell(this->nextState());
    }
}

#endif // DIMERREACTIONCAPTURING_ROLE_H

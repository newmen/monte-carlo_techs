#ifndef DIMERREACTIONSTABILIZING_ROLE_H
#define DIMERREACTIONSTABILIZING_ROLE_H

#include "ireacting_role.h"
#include "dimer_data.h"

template <class RData>
class DimerReactionStabilizingRole :
        public IReactingRole<DimerData>,
        public RData
{
public:
    double rate(const DimerData &dimer) const;
    void doIt(DimerData *dimer) const;
};

template <class RData>
double DimerReactionStabilizingRole<RData>::rate(const DimerData &dimer) const {
    return (dimer.first().cell() == this->prevState() && dimer.second().cell() == this->prevState()) ?
                this->k() : 0;
}

template <class RData>
void DimerReactionStabilizingRole<RData>::doIt(DimerData *dimer) const {
    dimer->first().setCell(this->nextState());
    dimer->second().setCell(this->nextState());
}

#endif // DIMERREACTIONSTABILIZING_ROLE_H

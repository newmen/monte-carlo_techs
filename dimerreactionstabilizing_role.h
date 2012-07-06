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
    void doIt(DimerData *const dimer) const;
};

template <class RData>
double DimerReactionStabilizingRole<RData>::rate(const DimerData &dimer) const {
    return (dimer.first->value() == this->prevState() && dimer.second->value() == this->prevState()) ?
                this->k() : 0;
}

template <class RData>
void DimerReactionStabilizingRole<RData>::doIt(DimerData *const dimer) const {
    dimer->first->setValue(this->nextState());
    dimer->second->setValue(this->nextState());
}

#endif // DIMERREACTIONSTABILIZING_ROLE_H

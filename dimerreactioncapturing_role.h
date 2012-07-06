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
    void doIt(DimerData *const dimer) const;
};

template <class RData>
double DimerReactionCapturingRole<RData>::rate(const DimerData &dimer) const {
    return ((dimer.first->value() == this->nextState() && dimer.second->value() == this->prevState()) ||
            (dimer.first->value() == this->prevState() && dimer.second->value() == this->nextState())) ?
                this->k() : 0;
}

template <class RData>
void DimerReactionCapturingRole<RData>::doIt(DimerData *const dimer) const {
    if (dimer->first->value() == this->prevState()) {
        dimer->first->setValue(this->nextState());
    } else {
        dimer->second->setValue(this->nextState());
    }
}

#endif // DIMERREACTIONCAPTURING_ROLE_H

#ifndef DIMERREACTIONEXCHANGING_ROLE_H
#define DIMERREACTIONEXCHANGING_ROLE_H

#include "ireacting_role.h"
#include "dimer_data.h"

template <class RData>
class DimerReactionExchangingRole :
        public IReactingRole<DimerData>,
        public RData
{
public:
    double rate(const DimerData &dimer) const;
    void doIt(DimerData *const dimer) const;
};

template <class RData>
double DimerReactionExchangingRole<RData>::rate(const DimerData &dimer) const {
    return ((dimer.first->value() == this->nextState() && dimer.second->value() == this->prevState()) ||
            (dimer.first->value() == this->prevState() && dimer.second->value() == this->nextState())) ?
                this->k() : 0;
}

template <class RData>
void DimerReactionExchangingRole<RData>::doIt(DimerData *const dimer) const {
    if (dimer->first->value() == this->nextState()) {
        dimer->first->setValue(this->prevState());
        dimer->second->setValue(this->nextState());
    } else {
        dimer->first->setValue(this->nextState());
        dimer->second->setValue(this->prevState());
    }
}

#endif // DIMERREACTIONEXCHANGING_ROLE_H

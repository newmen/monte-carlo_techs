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
    void doIt(DimerData *dimer) const;
};

template <class RData>
double DimerReactionExchangingRole<RData>::rate(const DimerData &dimer) const {
    return ((dimer.first().cell() == this->nextState() && dimer.second().cell() == this->prevState()) ||
            (dimer.first().cell() == this->prevState() && dimer.second().cell() == this->nextState())) ?
                this->k() : 0;
}

template <class RData>
void DimerReactionExchangingRole<RData>::doIt(DimerData *dimer) const {
    if (dimer->first().cell() == this->nextState()) {
        dimer->first().setCell(this->prevState());
        dimer->second().setCell(this->nextState());
    } else {
        dimer->first().setCell(this->nextState());
        dimer->second().setCell(this->prevState());
    }
}

#endif // DIMERREACTIONEXCHANGING_ROLE_H

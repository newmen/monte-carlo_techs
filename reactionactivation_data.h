#ifndef REACTIONACTIVATION_DATA_H
#define REACTIONACTIVATION_DATA_H

#include "rtreactor_context.h"

class ReactionActivationData
{
protected:
    ReactionActivationData(const RTReactorContext *reactor, double Ea);

    double expFactor(double additionalEnergy = 0) const;

private:
    const RTReactorContext *_reactor;
    double _Ea;
};

#endif // REACTIONACTIVATION_DATA_H

#ifndef REACTIONACTIVATION_DATA_H
#define REACTIONACTIVATION_DATA_H

#include "../contexts/rtreactor_context.h"

class ReactionActivationData
{
public:
    long double Ea() const { return _Ea; }

protected:
    ReactionActivationData(const RTReactorContext *reactor, long double Ea);

    long double expFactor(long double additionalEnergy = 0) const;

private:
    const RTReactorContext *_reactor;
    long double _Ea;
};

#endif // REACTIONACTIVATION_DATA_H

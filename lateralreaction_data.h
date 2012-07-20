#ifndef LATERALREACTION_DATA_H
#define LATERALREACTION_DATA_H

#include "reactionactivation_data.h"
#include "lateralsite_data.h"

class LateralReactionData : private ReactionActivationData
{
public:
    ~LateralReactionData();

protected:
    LateralReactionData(const RTReactorContext *reactor, double Ea, double epss[], int numOfSpecs);

    double expFactor(const LateralSiteData *site) const;

private:
    int _numOfSpecs;
    double *_epss;
};

#endif // LATERALREACTION_DATA_H

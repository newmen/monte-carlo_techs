#ifndef STABILIZATIONREACTING_ROLE_H
#define STABILIZATIONREACTING_ROLE_H

#include "reactionmigrating_role.h"

template <class RData>
class StabilizationReactingRole : public ReactionMigratingRole<RData>
{
public:
    void doIt(SiteData *site);

protected:
    int requiredNeighourState() const;
};

template <class RData>
void StabilizationReactingRole<RData>::doIt(SiteData *site) {
    updateNeighbour(site, this->nextState());
    site->setCell(this->nextState());
}

template <class RData>
int StabilizationReactingRole<RData>::requiredNeighourState() const {
    return this->prevState();
}

#endif // STABILIZATIONREACTING_ROLE_H

#ifndef STABILIZATIONREACTING_ROLE_H
#define STABILIZATIONREACTING_ROLE_H

#include "reactionmigrating_role.h"

template <class RData>
class StabilizationReactingRole : public ReactionMigratingRole<RData>
{
public:
    void doIt(SiteData *site);
};

template <class RData>
void StabilizationReactingRole<RData>::doIt(SiteData *site) {
    updateNeighbour(site, this->stableState());
    site->setCell(this->stableState());
}

#endif // STABILIZATIONREACTING_ROLE_H

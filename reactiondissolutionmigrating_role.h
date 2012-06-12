#ifndef REACTIONDISSOLUTIONMIGRATING_ROLE_H
#define REACTIONDISSOLUTIONMIGRATING_ROLE_H

#include "reactionmigrating_role.h"

template <class RData, int hopsNum>
class ReactionDissolutionMigratingRole : public ReactionMigratingRole<RData>
{
public:
    void doIt(SiteData *site);
};

template <class RData, int hopsNum>
void ReactionDissolutionMigratingRole<RData, hopsNum>::doIt(SiteData *site) {
    this->updateNeighbour(site, (this->migrationsNum() % hopsNum == 0) ? this->nextState() : this->prevState());
    site->setCell(this->nextState());

    this->incMigrationsNum();
}

#endif // REACTIONDISSOLUTIONMIGRATING_ROLE_H

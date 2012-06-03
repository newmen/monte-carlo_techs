#ifndef REACTIONMIGRATING_ROLE_H
#define REACTIONMIGRATING_ROLE_H

#include <functional>
#include "reacting_role.h"

template <class RData>
class ReactionMigratingRole : public ReactingRole<RData>
{
public:
    int couldBe(const SiteData &site) const;
    void doIt(SiteData *site);

protected:
    void updateNeighbour(const SiteData *site, int neighbourState);

private:
    std::function<void (int *)> validCaseLambda(std::function<void (int *)> innerLambda) const;
};

template <class RData>
int ReactionMigratingRole<RData>::couldBe(const SiteData &site) const {
    if (site.cell() != this->prevState()) return 0;

    int num = 0;
    site.neighboursIterator(validCaseLambda([&num](int *) {
        ++num;
    }));
    return num;
}

template <class RData>
void ReactionMigratingRole<RData>::doIt(SiteData *site) {
    updateNeighbour(site, this->prevState());
    ReactingRole<RData>::doIt(site);
}

template <class RData>
void ReactionMigratingRole<RData>::updateNeighbour(const SiteData *site, int neighbourState) {
    int randomIndex = rand() % couldBe(*site);
    int currCouldIndex = 0;
    site->neighboursIterator(validCaseLambda([this, &randomIndex, &currCouldIndex, &neighbourState](int *neighbour) {
        if (currCouldIndex++ == randomIndex) *neighbour = neighbourState;
    }));
}

template <class RData>
std::function<void (int *)> ReactionMigratingRole<RData>::validCaseLambda(std::function<void (int *)> innerLambda) const {
    return [this, &innerLambda](int *neighbour) {
        if (*neighbour == this->nextState()) innerLambda(neighbour);
    };
}

#endif // REACTIONMIGRATING_ROLE_H

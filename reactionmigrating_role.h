#ifndef REACTIONMIGRATING_ROLE_H
#define REACTIONMIGRATING_ROLE_H

#include <functional>
#include "reacting_role.h"

#include <iostream>

template <class Data>
class ReactionMigratingRole : public ReactingRole<Data>
{
public:
    int couldBe(const SiteData &site) const;
    void doIt(SiteData *site);

private:
    std::function<void (int *)> validCaseLambda(std::function<void (int *)> innerLambda) const;
};

template <class Data>
int ReactionMigratingRole<Data>::couldBe(const SiteData &site) const {
    if (site.cell() != this->prevState()) return 0;

    int num = 0;
    site.neighboursIterator(validCaseLambda([&num](int *) {
        ++num;
    }));
    return num;
}

template <class Data>
void ReactionMigratingRole<Data>::doIt(SiteData *site) {
    int randomIndex = rand() % couldBe(*site);
    int currCouldIndex = 0;
    site->neighboursIterator(validCaseLambda([this, &randomIndex, &currCouldIndex](int *neighbour) {
        if (currCouldIndex++ == randomIndex) *neighbour = this->prevState();
    }));
    ReactingRole<Data>::doIt(site);
}

template <class Data>
std::function<void (int *)> ReactionMigratingRole<Data>::validCaseLambda(std::function<void (int *)> innerLambda) const {
    return [this, &innerLambda](int *neighbour) {
        if (*neighbour == this->nextState()) innerLambda(neighbour);
    };
}

#endif // REACTIONMIGRATING_ROLE_H

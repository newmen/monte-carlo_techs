#ifndef REACTING_ROLE_H
#define REACTING_ROLE_H

#include "ireacting_role.h"

template <class RData>
class ReactingRole :
        public IReactingRole,
        public virtual RData
{
public:
    float rate() const;
    int couldBe(const SiteData &site) const;
    void doIt(SiteData *site);
};

template <class RData>
float ReactingRole<RData>::rate() const {
    return this->k();
}

template <class RData>
int ReactingRole<RData>::couldBe(const SiteData &site) const {
    return (site.cell() == this->prevState()) ? 1 : 0;
}

template <class RData>
void ReactingRole<RData>::doIt(SiteData *site) {
    site->setCell(this->nextState());
}

#endif // REACTING_ROLE_H

#ifndef SITEREACTING_ROLE_H
#define SITEREACTING_ROLE_H

#include "ireacting_role.h"
#include "site_data.h"

template <class SData>
class SiteReactingRole :
        public IReactingRole<SiteData>,
        public virtual SData
{
public:
    double rate(const SiteData &site) const;
    void doIt(SiteData *site) const;
};

template <class SData>
double SiteReactingRole<SData>::rate(const SiteData &site) const {
    return (site.cell() == this->prevState()) ? this->k() : 0;
}

template <class SData>
void SiteReactingRole<SData>::doIt(SiteData *site) const {
    site->setCell(this->nextState());
}

#endif // SITEREACTING_ROLE_H

#ifndef SIMULATING_ROLE_H
#define SIMULATING_ROLE_H

#include "site_data.h"

template <class AData>
class SimulatingRole : public AData
{
public:
    SimulatingRole() {}

    template <typename Lambda>
    void eachSite(const Lambda &lambda) const;
};

template <class AData>
template <typename Lambda>
void SimulatingRole<AData>::eachSite(const Lambda &lambda) const {
    this->coordsIterator([this, &lambda](int x, int y) {
        lambda(SharedSite(new SiteData(this->cell(x, y), x, y)));
    });
}

#endif // SIMULATING_ROLE_H

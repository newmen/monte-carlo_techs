#ifndef STORE_CONCENTRATIONS_CONTEXT_H
#define STORE_CONCENTRATIONS_CONTEXT_H

#include "store_context.h"
#include "../datas/area_data.h"

class StoreConcentrationsContext : public StoreContext
{
public:
    StoreConcentrationsContext(const std::string &fileName, const std::string &methodName, const AreaData *area, int numOfSpecs);

    void store(long double currentTime);

private:
    const AreaData *_area;
    const int _numOfSpecs;
};

#endif // STORE_CONCENTRATIONS_CONTEXT_H

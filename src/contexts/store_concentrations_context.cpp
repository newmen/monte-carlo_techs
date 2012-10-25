#include "store_concentrations_context.h"
#include "../roles/storingconcs_role.h"

StoreConcentrationsContext::StoreConcentrationsContext(const std::string &fileName, const std::string &methodName, const AreaData *area, int numOfSpecs) :
    StoreContext(fileName), _area(area), _numOfSpecs(numOfSpecs)
{
    if (isNew()) {
        out() << "# " << methodName << std::endl;
    }
}

void StoreConcentrationsContext::store(long double currentTime) {
    out() << currentTime;
    static_cast<const StoringConcsRole<AreaData> *>(_area)->store(out(), _numOfSpecs);
    out() << std::endl;
}

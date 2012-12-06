#include "storeshot_context.h"
#include "../roles/storingshot_role.h"

StoreShotContext::StoreShotContext(const std::string &fileName, const AreaData *area) :
    StoreContext(fileName), _area(area)
{
    if (isNew()) {
        out() << _area->sizeX() << "\n";
        out() << _area->sizeY() << "\n";
    }
}

void StoreShotContext::store(long double currentTime) {
    out() << currentTime << "\t";
    static_cast<const StoringShotRole<AreaData> *>(_area)->store(out());
    out() << std::endl;
}

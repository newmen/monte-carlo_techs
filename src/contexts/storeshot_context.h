#ifndef STORESHOT_CONTEXT_H
#define STORESHOT_CONTEXT_H

#include "store_context.h"
#include "../datas/area_data.h"

class StoreShotContext : public StoreContext
{
public:
    StoreShotContext(const std::string &fileName, const AreaData *area);

    void store(long double currentTime);

private:
    const AreaData *_area;
};

#endif // STORESHOT_CONTEXT_H

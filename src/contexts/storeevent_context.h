#ifndef STOREEVENT_CONTEXT_H
#define STOREEVENT_CONTEXT_H

#include "store_context.h"
#include "../datas/area_data.h"
#include "../datas/eventinfo_data.h"

class StoreEventContext : public StoreContext
{
public:
    StoreEventContext(const std::string &fileName, const AreaData &area);

    void storeByInfo(const EventInfoData &ei);

private:
    void storeSizes(const AreaData &area);
    void storeArea(const AreaData &area);
};

#endif // STOREEVENT_CONTEXT_H

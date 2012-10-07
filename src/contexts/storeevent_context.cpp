#include "storeevent_context.h"
#include "../datas/eventrecord_data.h"

StoreEventContext::StoreEventContext(const std::string &fileName, const AreaData &area) :
    StoreContext(fileName)
{
    storeSizes(area);
    storeArea(area);
}

void StoreEventContext::storeByInfo(const EventInfoData &ei) {
    EventRecordData eRecord(ei);
    out() << eRecord;
}

void StoreEventContext::storeSizes(const AreaData &area) {
    Point2D sizes;
    sizes.x = area.sizeX();
    sizes.y = area.sizeY();
    out().write((const char *)&sizes, sizeof(sizes));
}

void StoreEventContext::storeArea(const AreaData &area) {
    area.eachCell([this](CellType *const cell, CoordType x, CoordType y) {
        EventRecordData eRecord(cell, x, y);
        out() << eRecord;
    });
}


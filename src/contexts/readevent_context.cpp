#include "readevent_context.h"

ReadEventContext::ReadEventContext(const std::string &fileName) : ReadContext(fileName) {}

Point2D ReadEventContext::areaSizes() {
    Point2D sizes;
    in().read((char *)&sizes, sizeof(sizes));
    return sizes;
}

EventRecordData ReadEventContext::restoreEvent() {
    EventRecordData eRecord;
    in() >> eRecord;
    return eRecord;
}

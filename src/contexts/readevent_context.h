#ifndef READEVENT_CONTEXT_H
#define READEVENT_CONTEXT_H

#include "read_context.h"
#include "../datas/eventrecord_data.h"

class ReadEventContext : public ReadContext
{
public:
    ReadEventContext(const std::string &fileName);

    Point2D areaSizes();
    EventRecordData restoreEvent();
};

#endif // READEVENT_CONTEXT_H

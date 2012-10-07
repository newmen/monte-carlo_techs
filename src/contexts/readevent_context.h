#ifndef READEVENT_CONTEXT_H
#define READEVENT_CONTEXT_H

#include <fstream>
#include <string>
#include "../datas/eventrecord_data.h"

class ReadEventContext
{
public:
    ReadEventContext(const std::string &fileName);

    Point2D areaSizes();
    EventRecordData restoreEvent();

private:
    std::ifstream _inFile;
};

#endif // READEVENT_CONTEXT_H

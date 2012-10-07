#include <iostream>
#include "readevent_context.h"

ReadEventContext::ReadEventContext(const std::string &fileName) : _inFile(fileName)
{
    if (!_inFile) {
        std::cerr << "File " << fileName << " open error!" << std::endl;
        exit(1);
    }
}

Point2D ReadEventContext::areaSizes() {
    Point2D sizes;
    _inFile.read((char *)&sizes, sizeof(sizes));
    return sizes;
}

EventRecordData ReadEventContext::restoreEvent() {
    EventRecordData eRecord;
    _inFile >> eRecord;
    return eRecord;
}

#ifndef READSHOT_CONTEXT_H
#define READSHOT_CONTEXT_H

#include "read_context.h"
#include "../datas/area_data.h"

class ReadShotContext : public ReadContext
{
public:
    ReadShotContext(const std::string &fileName);

    Point2D areaSizes();
    double setShotToArea(AreaData *area);
};

#endif // READSHOT_CONTEXT_H

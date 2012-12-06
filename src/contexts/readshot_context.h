#ifndef READSHOT_CONTEXT_H
#define READSHOT_CONTEXT_H

#include <string>
#include "read_context.h"
#include "../datas/area_data.h"

class ReadShotContext : public ReadContext
{
public:
    ReadShotContext(const std::string &fileName);

    Point2D areaSizes();
    double setShotToArea(AreaData *area);
    double setLastShotToArea(AreaData *area);

private:
    std::string getLine();
    double readFromLine(const std::string &line, AreaData *area);
};

#endif // READSHOT_CONTEXT_H

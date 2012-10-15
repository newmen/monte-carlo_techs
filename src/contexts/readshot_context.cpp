#include <sstream>
#include "readshot_context.h"

ReadShotContext::ReadShotContext(const std::string &fileName) : ReadContext(fileName) {}

Point2D ReadShotContext::areaSizes() {
    Point2D p;
    in() >> p.x >> p.y;
    return p;
}

double ReadShotContext::setShotToArea(AreaData *area) {
    std::string line;
    std::getline(in(), line);
    if (line == "") return -1;

    std::stringstream ss(line);

    double currentTime = 0;
    ss >> currentTime;

    area->eachCell([this, &ss](CellType *value, CoordType, CoordType) {
        char cv;
        ss.get(cv);
        *value = (int)cv - 48;
    });

    return currentTime;
}


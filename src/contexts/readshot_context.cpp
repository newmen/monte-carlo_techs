#include <sstream>
#include "readshot_context.h"

#define END_VALUE -1

ReadShotContext::ReadShotContext(const std::string &fileName) : ReadContext(fileName) {}

Point2D ReadShotContext::areaSizes() {
    Point2D p;
    in() >> p.x >> p.y;
    getLine(); // empty line for '\n'
    return p;
}

double ReadShotContext::setShotToArea(AreaData *area) {
    std::string line = getLine();
    if (line == "") return END_VALUE;
    return readFromLine(line, area);
}

double ReadShotContext::setLastShotToArea(AreaData *area) {
    std::string line = "";
    while (true) {
        std::string nextLine = getLine();
        if (nextLine == "") break;
        else line = nextLine;
    }

    if (line == "") return END_VALUE;
    else return readFromLine(line, area);
}

std::string ReadShotContext::getLine() {
    std::string line;
    std::getline(in(), line);
    return line;
}

double ReadShotContext::readFromLine(const std::string &line, AreaData *area) {
    std::stringstream ss(line);

    double currentTime = 0;
    ss >> currentTime;
    char tab;
    ss.get(tab);

    area->eachCell([this, &ss](CellType *value, CoordType, CoordType) {
        char cv;
        ss.get(cv);
        *value = (int)cv - 48;
    });

    return currentTime;
}


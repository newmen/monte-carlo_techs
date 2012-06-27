#ifndef STORE_CONTEXT_H
#define STORE_CONTEXT_H

#include <fstream>
#include "area_data.h"

class StoreContext
{
public:
    StoreContext(const AreaData *area, const char *fileName, const char *methodName);

    void store(double dt);

private:
    const AreaData *_area;
    std::ofstream _outFile;
    double _totalTime;
};

#endif // STORE_CONTEXT_H

#ifndef STORE_CONTEXT_H
#define STORE_CONTEXT_H

#include <fstream>
#include <string>
#include "area_data.h"

class StoreContext
{
public:
    StoreContext(const AreaData *area, int numOfSpecs, const std::string &fileName, const std::string &methodName);

    void store(double dt);

private:
    const AreaData *_area;
    const int _numOfSpecs;
    std::ofstream _outFile;
    double _totalTime;
};

#endif // STORE_CONTEXT_H

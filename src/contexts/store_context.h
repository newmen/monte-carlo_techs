#ifndef STORE_CONTEXT_H
#define STORE_CONTEXT_H

#include <fstream>
#include <string>
#include "../datas/area_data.h"

class StoreContext
{
public:
    StoreContext(const AreaData *area, int numOfSpecs, const std::string &fileName, const std::string &methodName);

    void store(long double currentTime);

private:
    const AreaData *_area;
    const int _numOfSpecs;
    std::ofstream _outFile;
};

#endif // STORE_CONTEXT_H

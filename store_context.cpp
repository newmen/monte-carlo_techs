#include <iostream>
#include "store_context.h"
#include "storing_role.h"

StoreContext::StoreContext(const AreaData *area, const char *fileName, const char *methodName) :
    _area(area), _outFile(fileName)
{
    if (!_outFile) {
        std::cerr << "File " << fileName << " open error!" << std::endl;
        exit(1);
    } else {
        _outFile << "# " << methodName << std::endl;
    }
}

void StoreContext::store(float dt) {
    _totalTime += dt;

    _outFile << _totalTime;
    static_cast<const StoringRole<AreaData> *>(_area)->store(_outFile);
    _outFile << std::endl;
}

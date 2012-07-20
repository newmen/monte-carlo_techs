#include <iostream>
#include "store_context.h"
#include "storing_role.h"

StoreContext::StoreContext(const AreaData *area, int numOfSpecs, const std::string &fileName, const std::string &methodName) :
    _area(area), _numOfSpecs(numOfSpecs), _outFile(fileName)
{
    if (!_outFile) {
        std::cerr << "File " << fileName << " open error!" << std::endl;
        exit(1);
    } else {
        _outFile << "# " << methodName << std::endl;
    }
}

void StoreContext::store(double dt) {
    _totalTime += dt;

    _outFile << _totalTime;
    static_cast<const StoringRole<AreaData> *>(_area)->store(_outFile, _numOfSpecs);
    _outFile << std::endl;
}

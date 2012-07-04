#ifndef PERFORMANCESAVER_H
#define PERFORMANCESAVER_H

#include <map>
#include <string>
#include <vector>
#include "pathbuilder.h"

class PerformanceSaver {
public:
    PerformanceSaver(const PathBuilder *pathBuilder);
    ~PerformanceSaver();

    void storeName(const std::string &mcName);
    void storeValue(const std::string &fileName, unsigned int size, double value);

private:
    const PathBuilder *_pathBuilder;
    std::vector<std::string> _dataNames;
    std::map<std::string, std::map<unsigned int, std::vector<double> > > _dataValues;
};

#endif // PERFORMANCESAVER_H

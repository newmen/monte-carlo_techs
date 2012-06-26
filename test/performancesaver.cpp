#include "performancesaver.h"

#include <fstream>
#include <iostream>

PerformanceSaver::PerformanceSaver(const PathBuilder *pathBuilder) : _pathBuilder(pathBuilder) {}

PerformanceSaver::~PerformanceSaver() {
    if (_dataNames.empty()) return;

    const char ext[] = "prf";

    bool filesAlreadyExists = true;
    std::ifstream temp;
    for (auto filePair = _dataValues.cbegin(); filePair != _dataValues.cend(); ++filePair) {
        std::string fullFilePath = _pathBuilder->buildPath(filePair->first.c_str(), ext);
        temp.open(fullFilePath.c_str());
        if (!temp) {
            std::cout << fullFilePath << " does not exists" << std::endl;
            filesAlreadyExists = false;
            break;
        } else {
            temp.close();
        }
    }

    std::ofstream out;
    for (auto filePair = _dataValues.cbegin(); filePair != _dataValues.cend(); ++filePair) {
        std::string fullFilePath = _pathBuilder->buildPath(filePair->first.c_str(), ext);
        out.open(fullFilePath.c_str(), ((filesAlreadyExists) ? std::ios_base::app : std::ios_base::trunc));
        if (!filesAlreadyExists) {
            out << "#";
            for (const std::string &name : _dataNames) out << "\t" << name;
            out << "\n";
        }

        for (auto p = filePair->second.cbegin(); p != filePair->second.cend(); ++p) {
            out << p->first;
            for (double value : p->second) out << "\t" << value;
            out << std::endl;
        }
        out.close();

        _pathBuilder->printFileWasSaved(fullFilePath);
    }
}

void PerformanceSaver::storeName(const char *mcName) {
    _dataNames.push_back(mcName);
}

void PerformanceSaver::storeValue(const char *fileName, unsigned int size, double value) {
    _dataValues[fileName][size].push_back(value);
}


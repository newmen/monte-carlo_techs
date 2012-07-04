#include "pathbuilder.h"

#include <sstream>
#include <iostream>

PathBuilder::PathBuilder(const std::string &resultDir) : _resultDir(resultDir) {
}

const std::string PathBuilder::buildPath(const std::string &fileName, const std::string &ext) const {
    std::stringstream ss;
    ss << "results/" << fileName << "." << ext;
    return ss.str();
}

void PathBuilder::printFileWasSaved(const std::string &fileName) const {
    std::cout << fileName << " file saved\n" << std::endl;
}

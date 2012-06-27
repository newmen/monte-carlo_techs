#include "pathbuilder.h"

#include <sstream>
#include <iostream>

PathBuilder::PathBuilder(const char *resultDir) : _resultDir(resultDir) {
}

const char *PathBuilder::buildPath(const char *fileName, const char *ext) const {
    std::stringstream ss;
    ss << "results/" << fileName << "." << ext;
    return ss.str().c_str();
}

void PathBuilder::printFileWasSaved(const std::string &fileName) const {
    std::cout << fileName << " file saved\n" << std::endl;
}

#ifndef PATHBUILDER_H
#define PATHBUILDER_H

#include <string>

class PathBuilder
{
public:
    PathBuilder(const std::string &resultDir);

    const std::string buildPath(const std::string &fileName, const std::string &ext) const;
    void printFileWasSaved(const std::string &fileName) const;

private:
    std::string _resultDir;
};

#endif // PATHBUILDER_H

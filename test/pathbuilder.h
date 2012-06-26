#ifndef PATHBUILDER_H
#define PATHBUILDER_H

#include <string>

class PathBuilder
{
public:
    PathBuilder(const char *resultDir);

    const char *buildPath(const char *fileName, const char *ext) const;
    void printFileWasSaved(const std::string &fileName) const;

private:
    std::string _resultDir;
};

#endif // PATHBUILDER_H

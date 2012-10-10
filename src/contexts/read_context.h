#ifndef READ_CONTEXT_H
#define READ_CONTEXT_H

#include <fstream>
#include <string>
#include "../datas/point2d.h"

class ReadContext
{
public:
    virtual ~ReadContext() {}
    virtual Point2D areaSizes() = 0;

protected:
    ReadContext(const std::string &fileName);
    std::ifstream &in() { return _inFile; }

private:
    std::ifstream _inFile;
};

#endif // READ_CONTEXT_H

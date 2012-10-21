#ifndef STORE_CONTEXT_H
#define STORE_CONTEXT_H

#include <fstream>
#include <string>

class StoreContext
{
protected:
    StoreContext(const std::string &fileName);

    std::ofstream &out();
    bool isNew();

private:
    std::ofstream _outFile;
};

#endif // STORE_CONTEXT_H

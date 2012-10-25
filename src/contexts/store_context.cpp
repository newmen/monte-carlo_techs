//#include <cstdlib>
#include <iostream>
#include "store_context.h"

StoreContext::StoreContext(const std::string &fileName) : _outFile(fileName) {
    if (!_outFile) {
        std::cerr << "File " << fileName << " open error!" << std::endl;
        exit(1);
    }
}

std::ofstream &StoreContext::out() {
    return _outFile;
}

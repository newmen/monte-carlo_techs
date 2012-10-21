#include <iostream>
#include "read_context.h"

ReadContext::ReadContext(const std::string &fileName) : _inFile(fileName) {
    if (!_inFile) {
        std::cerr << "File " << fileName << " open error!" << std::endl;
        exit(1);
    }
}

void ReadContext::close() {
    _inFile.close();
}

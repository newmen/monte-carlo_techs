#ifndef ABCDREACTOR_DATA_H
#define ABCDREACTOR_DATA_H

#include "reactorbase_data.h"
#include "cell_data.h"

class ABCDReactorData : public ReactorBaseData
{
public:
    ABCDReactorData();

    CellData *createCell(int *cell, int x, int y) const;
    void solve(const std::string &fileName, double maxTime) const;
};

#endif // ABCDREACTOR_DATA_H

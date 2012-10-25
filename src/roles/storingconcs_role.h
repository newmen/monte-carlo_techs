#ifndef STORINGCONCS_ROLE_H
#define STORINGCONCS_ROLE_H

#include <ostream>
#include "../datas/cell_data.h"

template <class AData>
class StoringConcsRole : public AData
{
public:
    void store(std::ostream &os, int numOfSpecs) const;
};

template <class AData>
void StoringConcsRole<AData>::store(std::ostream &os, int numOfSpecs) const {
    int *statesAcc = new int[numOfSpecs];
    for (int i = 0; i < numOfSpecs; ++i) statesAcc[i] = 0;

    this->eachCell([this, &statesAcc, numOfSpecs](CellType *const value, CoordType, CoordType) {
        if (*value > 1 && (*value - 2) < numOfSpecs) ++statesAcc[*value - 2];
    });

    for (int i = 0; i < numOfSpecs; ++i) {
        os << "\t" << (double)statesAcc[i] / this->size();
    }
}

#endif // STORINGCONCS_ROLE_H

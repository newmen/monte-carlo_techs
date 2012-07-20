#ifndef STORING_ROLE_H
#define STORING_ROLE_H

#include <ostream>
#include "cell_data.h"

template <class AData>
class StoringRole : public AData
{
public:
    void store(std::ostream &os, int numOfSpecs) const;
};

template <class AData>
void StoringRole<AData>::store(std::ostream &os, int numOfSpecs) const {
    int *statesAcc = new int[numOfSpecs];
    for (int i = 0; i < numOfSpecs; ++i) statesAcc[i] = 0;

    this->eachCell([this, &statesAcc, numOfSpecs](int *const value, int, int) {
        if (*value > 1 && *value - 2 < numOfSpecs) ++statesAcc[*value - 2];
    });

    for (int i = 0; i < numOfSpecs; ++i) {
        os << "\t" << (float)statesAcc[i] / this->size();
    }
}

#endif // STORING_ROLE_H

#ifndef STORING_ROLE_H
#define STORING_ROLE_H

#include <ostream>
#include "cell_data.h"

#define STATES_NUM 4

template <class AData>
class StoringRole : public AData
{
public:
    void store(std::ostream &os) const;
};

template <class AData>
void StoringRole<AData>::store(std::ostream &os) const {
    int statesAcc[STATES_NUM];
    for (int i = 0; i < STATES_NUM; ++i) statesAcc[i] = 0;

    this->eachCell([this, &statesAcc](int *const value, int, int) {
        if (*value > 1) ++statesAcc[*value - 2];
    });

    for (int i = 0; i < STATES_NUM; ++i) {
        os << "\t" << (float)statesAcc[i] / this->size();
    }
}

#endif // STORING_ROLE_H

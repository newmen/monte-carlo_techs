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

    this->eachCell([this, &statesAcc](CellData *const cell) {
        int state = cell->value();
        if (state > 1) ++statesAcc[state - 2];
    });

    for (int i = 0; i < STATES_NUM; ++i) {
        os << "\t" << (float)statesAcc[i] / this->size();
    }
}

#endif // STORING_ROLE_H

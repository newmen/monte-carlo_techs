#ifndef STORING_ROLE_H
#define STORING_ROLE_H

#include <ostream>

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

    this->coordsIterator([this, &statesAcc](int x, int y) {
        int state = *this->cell(x, y);
        if (state > 1) ++statesAcc[state - 2];
    });

    int totalNumOfCells = this->sizeX() * this->sizeY();
    for (int i = 0; i < STATES_NUM; ++i) {
        os << "\t" << (float)statesAcc[i] / totalNumOfCells;
    }
}

#endif // STORING_ROLE_H

#ifndef SIMULATING_ROLE_H
#define SIMULATING_ROLE_H

#include <functional>

#ifndef NEIGHBOURS_NUM
// страшный и ужасный костыль
#define NEIGHBOURS_NUM 4
#endif

template <class AData>
class SimulatingRole : public AData
{
public:
    SimulatingRole() {}

    void cellsWithNeighsIter(std::function<void (int *, int **)> lambda) const;

private:
    int torus(int curr, int size) const;
    int *neighbour(int nx, int ny) const;
    int **neighbours(int x, int y) const;
};

template <class AData>
void SimulatingRole<AData>::cellsWithNeighsIter(std::function<void (int *, int **)> lambda) const {
    this->coordsIterator([this, &lambda](int x, int y) {
        int **nbrs = this->neighbours(x, y);
        lambda(this->cell(x, y), nbrs);
        delete [] nbrs;
    });
}

template <class AData>
int SimulatingRole<AData>::torus(int curr, int size) const {
    if (curr < 0) return size - 1;
    else if (curr == size) return 0;
    else return curr;
}

template <class AData>
int *SimulatingRole<AData>::neighbour(int nx, int ny) const {
    return this->cell(torus(nx, this->sizeX()), torus(ny, this->sizeY()));
}

template <class AData>
int **SimulatingRole<AData>::neighbours(int x, int y) const {
    int **nbrs = new int *[NEIGHBOURS_NUM];
    nbrs[0] = neighbour(x, y - 1);
    nbrs[1] = neighbour(x + 1, y);
    nbrs[2] = neighbour(x, y + 1);
    nbrs[3] = neighbour(x - 1, y);

    return nbrs;
}

#endif // SIMULATING_ROLE_H

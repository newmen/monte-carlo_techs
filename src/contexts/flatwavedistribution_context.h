#ifndef FLATWAVEDISTRIBUTION_CONTEXT_H
#define FLATWAVEDISTRIBUTION_CONTEXT_H

#include "wavedistribution_context.h"

class FlatWaveDistributionContext : public WaveDistributionContext
{
public:
    FlatWaveDistributionContext(float *fourPoints, int num) : WaveDistributionContext(fourPoints, num) {}

protected:
    void selectAppropriateConcs(CoordType sizeX, CoordType, CoordType x, CoordType) {
        CoordType partSize = sizeX / 4;
        CoordType seekX = x;
        while (seekX > partSize) { seekX -= partSize; }

        float *concs = new float[num()];
        if (seekX < partSize / 4) {
            setupConcs(concs, 0);
        } else if (seekX < partSize / 2) {
            setupConcs(concs, 1);
        } else if (seekX < partSize * 3 / 4) {
            setupConcs(concs, 2);
        } else {
            setupConcs(concs, 3);
        }
        setConcs(concs);
        delete [] concs;
    }
};

#endif // FLATWAVEDISTRIBUTION_CONTEXT_H

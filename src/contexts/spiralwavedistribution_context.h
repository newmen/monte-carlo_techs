#ifndef SPIRALWAVEDISTRIBUTION_CONTEXT_H
#define SPIRALWAVEDISTRIBUTION_CONTEXT_H

#include "wavedistribution_context.h"

class SpiralWaveDistributionContext : public WaveDistributionContext
{
public:
    SpiralWaveDistributionContext(float *fourPoints, int num) : WaveDistributionContext(fourPoints, num) {}

protected:
    void selectAppropriateConcs(CoordType sizeX, CoordType sizeY, CoordType x, CoordType y) {
        float *concs = new float[num()];
        if (y < sizeY / 2 && x < sizeX / 2) {
            setupConcs(concs, 0);
        } else if (y < sizeY / 2 && x >= sizeX / 2) {
            setupConcs(concs, 1);
        } else if (y >= sizeY / 2 && x >= sizeX / 2) {
            setupConcs(concs, 2);
        } else { // if (y >= sizeY / 2 && x < sizeX / 2)
            setupConcs(concs, 3);
        }
        setConcs(concs);
        delete [] concs;
    }
};

#endif // SPIRALWAVEDISTRIBUTION_CONTEXT_H

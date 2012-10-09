#include "wavedistribution_context.h"

WaveDistributionContext::WaveDistributionContext(float *fourPoints, int num) :
    SimpleDistributionContext(num)
{
    int total = num * 4;
    _fourPoints = new float[total];
    for (int i = 0; i < total; ++i) _fourPoints[i] = fourPoints[i];
}

void WaveDistributionContext::setupConcs(float *concs, int part)  {
    int j = 0;
    for (int i = part * num(); i < (part + 1) * num(); ++i) {
        concs[j++] = _fourPoints[i];
    }
}

WaveDistributionContext::~WaveDistributionContext() {
    delete [] _fourPoints;
}

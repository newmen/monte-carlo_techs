#ifndef WAVEDISTRIBUTION_CONTEXT_H
#define WAVEDISTRIBUTION_CONTEXT_H

#include "simpledistribution_context.h"

class WaveDistributionContext : public SimpleDistributionContext
{
public:
    ~WaveDistributionContext();

protected:
    WaveDistributionContext(float *fourPoints, int num);

    void setupConcs(float *concs, int part);

private:
    float *_fourPoints;
};

#endif // WAVEDISTRIBUTION_CONTEXT_H

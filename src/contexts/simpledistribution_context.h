#ifndef SIMPLEDISTRIBUTION_CONTEXT_H
#define SIMPLEDISTRIBUTION_CONTEXT_H

#include "basedistribution_context.h"

class SimpleDistributionContext : public BaseDistributionContext
{
public:
    SimpleDistributionContext(float *concs, int num);
    ~SimpleDistributionContext();

    int value() const;

protected:
    SimpleDistributionContext(int num);

    void setConcs(const float *concs);
    int num() const { return _num; }

private:
    void allocateMemory();

    int _num;
    float *_concs;
};

#endif // SIMPLEDISTRIBUTION_CONTEXT_H

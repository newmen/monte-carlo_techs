#include "simpledistribution_context.h"

SimpleDistributionContext::SimpleDistributionContext(int num) : _num(num) {
    allocateMemory();
}

SimpleDistributionContext::SimpleDistributionContext(float *concs, int num) : _num(num) {
    allocateMemory();
    setConcs(concs);
}

SimpleDistributionContext::~SimpleDistributionContext() {
    delete [] _concs;
}

int SimpleDistributionContext::value() const {
    float r = (float)(rand() % 100) / 100;
    for (int i = 0; i < _num; ++i) {
        if (r < _concs[i]) return i + 2;
        else r -= _concs[i];
    }
    return BaseDistributionContext::value();
}

void SimpleDistributionContext::setConcs(const float *concs) {
    for (int i = 0; i < _num; ++i) _concs[i] = concs[i];
}

void SimpleDistributionContext::allocateMemory() {
    _concs = new float[_num];
}

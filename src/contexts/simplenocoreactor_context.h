#ifndef SIMPLENOCOREACTOR_CONTEXT_H
#define SIMPLENOCOREACTOR_CONTEXT_H

#include "lateralreactor_context.h"

class SimpleNOCOReactorContext : public LateralReactorContext
{
public:
    SimpleNOCOReactorContext();

    int numOfSpecs() const { return 2; }
    long double maxTime() const { return 200.0; }
    long double timeStep() const { return 0.1; }
//    long double timeStep() const { return 0.0405; }

    bool isTorusArea() const;

protected:
    BaseDistributionContext *createDistrubutor() const;
    void solveToOut(std::ostream &out) const;
};

#endif // SIMPLENOCOREACTOR_CONTEXT_H

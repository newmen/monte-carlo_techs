#ifndef FULLNOCOREACTOR_CONTEXT_H
#define FULLNOCOREACTOR_CONTEXT_H

#include "lateralreactor_context.h"

class FullNOCOReactorContext : public LateralReactorContext
{
public:
    FullNOCOReactorContext();

    int numOfSpecs() const { return 3; }
    long double maxTime() const { return 500.0; }
    long double timeStep() const { return 0.1; }
//    long double timeStep() const { return 0.0405; }

    bool isTorusArea() const;

protected:
    BaseDistributionContext *createDistrubutor() const;
    void solveToOut(std::ostream &out) const;
};

#endif // FULLNOCOREACTOR_CONTEXT_H

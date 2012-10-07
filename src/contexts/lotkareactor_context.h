#ifndef LOTKAREACTOR_CONTEXT_H
#define LOTKAREACTOR_CONTEXT_H

#include "basereactor_context.h"

class LotkaReactorContext : public BaseReactorContext
{
public:
    LotkaReactorContext();

    int numOfSpecs() const { return 2; }
    long double maxTime() const { return 5000; }
    long double timeStep() const { return 1; }

protected:
    BaseDistributionContext *createDistrubutor() const;
    void solveToOut(std::ostream &out) const;
};

#endif // LOTKAREACTOR_CONTEXT_H

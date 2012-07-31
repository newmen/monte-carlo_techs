#ifndef LOTKATHREEREACTOR_CONTEXT_H
#define LOTKATHREEREACTOR_CONTEXT_H

#include "basereactor_context.h"

class LotkaThreeReactorContext : public BaseReactorContext
{
public:
    LotkaThreeReactorContext();

    int numOfSpecs() const { return 3; }
    long double maxTime() const { return 5000; }
    long double timeStep() const { return 1; }

protected:
    void solveToOut(std::ostream &out) const;
};

#endif // LOTKATHREEREACTOR_CONTEXT_H

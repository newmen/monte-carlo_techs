#ifndef LOTKATHREEREACTOR_CONTEXT_H
#define LOTKATHREEREACTOR_CONTEXT_H

#include "reactorbase_context.h"

class LotkaThreeReactorContext : public ReactorBaseContext
{
public:
    LotkaThreeReactorContext();

    int numOfSpecs() const { return 3; }
    long double maxTime() const { return 5000; }

protected:
    void solveToOut(std::ostream &out) const;
};

#endif // LOTKATHREEREACTOR_CONTEXT_H

#ifndef LOTKAREACTOR_CONTEXT_H
#define LOTKAREACTOR_CONTEXT_H

#include "reactorbase_context.h"

class LotkaReactorContext : public ReactorBaseContext
{
public:
    LotkaReactorContext();

    int numOfSpecs() const { return 2; }
    double maxTime() const { return 2250; }

protected:
    void solveToOut(std::ostream &out) const;
};

#endif // LOTKAREACTOR_CONTEXT_H

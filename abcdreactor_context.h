#ifndef ABCDREACTOR_CONTEXT_H
#define ABCDREACTOR_CONTEXT_H

#include "reactorbase_context.h"
#include "cell_data.h"

class ABCDReactorContext : public ReactorBaseContext
{
public:
    ABCDReactorContext();

    int numOfSpecs() const { return 4; }
    double maxTime() const { return 2.0; }

protected:
    void solveToOut(std::ostream &out) const;
};

#endif // ABCDREACTOR_CONTEXT_H

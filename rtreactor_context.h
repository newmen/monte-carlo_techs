#ifndef RTREACTOR_CONTEXT_H
#define RTREACTOR_CONTEXT_H

#include "reactorbase_context.h"

class RTReactorContext : public ReactorBaseContext
{
public:
    double RT() const;

protected:
    RTReactorContext(double T);

private:
    double _T;
};

#endif // RTREACTOR_CONTEXT_H

#ifndef RTREACTOR_CONTEXT_H
#define RTREACTOR_CONTEXT_H

#include "basereactor_context.h"

class RTReactorContext : public BaseReactorContext
{
public:
    double RT() const;

protected:
    RTReactorContext(double T);

private:
    double _T;
};

#endif // RTREACTOR_CONTEXT_H

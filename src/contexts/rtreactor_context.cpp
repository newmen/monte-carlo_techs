#include "rtreactor_context.h"

RTReactorContext::RTReactorContext(double T) : _T(T) {}

double RTReactorContext::RT() const {
    return _T * 1.987;
}

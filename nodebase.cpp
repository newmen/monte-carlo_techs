#include "nodebase.h"

NodeBase::NodeBase(int level) : _sum(0), _parent(0), _level(level) {}

void NodeBase::accSum(float sum) {
    _sum += sum;
    if (_parent) _parent->accSum(sum);
}

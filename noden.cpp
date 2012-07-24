#include "noden.h"

#include <iostream>

NodeN::NodeN(int width, int level) : NodeBase(level), _width(width), _numberOfChilds(0) {
    _childs = new NodeBase *[_width];
    for (int i = 0; i < _width; ++i) _childs[i] = 0;
}

NodeN::~NodeN() {
    for (int i = 0; i < _numberOfChilds; ++i) delete _childs[i];
    delete [] _childs;
}

void NodeN::add(INodeS *node) {
    if (level() > 1) {
        if (_numberOfChilds == 0 || last()->isFull()) store(new NodeN(_width, level() - 1));
        last()->add(node);
    } else {
        store(node);
    }
    _sum += node->sum();
}

void NodeN::add(NodeN *node) {
    store(node);
    _sum += node->sum();
}

bool NodeN::isFull() const {
    if (_numberOfChilds < _width) return false;
    if (level() == 1) return true;
    return last()->isFull();
}

INodeS *NodeN::find(long double *r) const {
    for (int i = 0; i < _numberOfChilds; ++i) {
        long double childSum = _childs[i]->sum();
        if (*r < childSum) {
            if (level() == 1) {
                return static_cast<INodeS *>(_childs[i]);
            } else {
                return static_cast<NodeN *>(_childs[i])->find(r);
            }
        } else {
            *r -= childSum;
        }
    }
    return 0; // happen when need reCount
}

void NodeN::reCount() {
    _sum = 0;
    for (int i = 0; i < _numberOfChilds; ++i) {
        _childs[i]->reCount();
        _sum += _childs[i]->sum();
    }
}

bool NodeN::diagnoze() const {
    static int n = 0;
    ++n;

    long double childsSum  = 0;
    for (int i = 0; i < _numberOfChilds; ++i) {
        if (!_childs[i]->diagnoze()) return false;

        childsSum += _childs[i]->sum();
    }

    if (!lessThanEps(sum() - childsSum)) {
        std::cerr << n << ". Trouble on N" << level() << " level!\n"
                  << "diff: " << sum() - childsSum << std::endl;
        return false;
    }
    return true;
}

void NodeN::store(NodeBase *node) {
    node->setParent(this);
    _childs[_numberOfChilds++] = node;
}

NodeN *NodeN::last() const {
    return static_cast<NodeN *>(_childs[_numberOfChilds - 1]);
}

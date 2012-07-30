#include "mctree.h"

MCTree::MCTree(int width) : _width(width) {
    _root = new NodeN(_width, 1);
}

MCTree::~MCTree() {
    delete _root;
}

void MCTree::add(INodeS *node) {
    node->initSum();
    if (_root->isFull()) {
        NodeN *newRoot = new NodeN(_width, _root->level() + 1);
        newRoot->add(_root);
        _root = newRoot;
    }
    _root->add(node);
}

long double MCTree::sum() const {
    return _root->sum();
}

INodeS *MCTree::find(long double *r) const {
    return _root->find(r);
}

void MCTree::reCount(const SimulationBaseContext *simulationContext) {
    _root->reCount(simulationContext);
}

bool MCTree::diagnostic() const {
    return _root->diagnoze();
}


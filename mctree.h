#ifndef MCTREE_H
#define MCTREE_H

#include <functional>
#include "site_data.h"
#include "nodes.h"
#include "noden.h"

template <int width>
class MCTree
{
public:
    MCTree();
    ~MCTree();

    void add(INodeS *node);
    double sum() const;

    INodeS *find(double *r) const;

private:
    NodeN<width> *_root;
};

template <int width>
MCTree<width>::MCTree() {
    _root = new NodeN<width>(1);
}

template <int width>
MCTree<width>::~MCTree() {
    delete _root;
}

template <int width>
void MCTree<width>::add(INodeS *node) {
    if (_root->isFull()) {
        NodeN<width> *newRoot = new NodeN<width>(_root->level() + 1);
        newRoot->add(_root);
        _root = newRoot;
    }
    _root->add(node);
}

template <int width>
double MCTree<width>::sum() const {
    return _root->sum();
}

template <int width>
INodeS *MCTree<width>::find(double *r) const {
    return _root->find(r);
}

#endif // MCTREE_H

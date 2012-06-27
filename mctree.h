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

    void add(NodeS *node);
    double sum() const;

    NodeS *find(double *r) const;

    void diagnostic() const;

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
void MCTree<width>::add(NodeS *node) {
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
NodeS *MCTree<width>::find(double *r) const {
    return _root->find(r);
}

template <int width>
void MCTree<width>::diagnostic() const {
    _root->diagnoze();
}

#endif // MCTREE_H

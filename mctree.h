#ifndef MCTREE_H
#define MCTREE_H

#include "noden.h"
#include "nodes.h"

template <class PerData>
class MCTree
{
public:
    MCTree(int width);
    ~MCTree();

    void add(NodeS<PerData> *node);
    double sum() const;

    NodeS<PerData> *find(double *r) const;

    void diagnostic() const;

private:
    int _width;
    NodeN *_root;
};

template <class PerData>
MCTree<PerData>::MCTree(int width) : _width(width) {
    _root = new NodeN(_width, 1);
}

template <class PerData>
MCTree<PerData>::~MCTree() {
    delete _root;
}

template <class PerData>
void MCTree<PerData>::add(NodeS<PerData> *node) {
    node->initSum();
    if (_root->isFull()) {
        NodeN *newRoot = new NodeN(_width, _root->level() + 1);
        newRoot->add(_root);
        _root = newRoot;
    }
    _root->add(node);
}

template <class PerData>
double MCTree<PerData>::sum() const {
    return _root->sum();
}

template <class PerData>
NodeS<PerData> *MCTree<PerData>::find(double *r) const {
    return static_cast<NodeS<PerData> *>(_root->find(r));
}

template <class PerData>
void MCTree<PerData>::diagnostic() const {
    _root->diagnoze();
}

#endif // MCTREE_H

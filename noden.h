#ifndef NODEN_H
#define NODEN_H

#include "nodebase.h"
#include "nodes.h"

#include <iostream>

class NodeN : public NodeBase
{
public:
    NodeN(int width, int level);
    ~NodeN();

    void add(NodeS *node);
    void add(NodeN *node);
    bool isFull() const;

    NodeS *find(double *r) const;

    void diagnoze() const;

private:
    void store(NodeBase *node);
    NodeN *last() const;

private:
    NodeBase **_childs;
    int _width, _numberOfChilds;
};

#endif // NODEN_H

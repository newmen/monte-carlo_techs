#ifndef MCTREE_H
#define MCTREE_H

#include <functional>
#include "nodes.h"
#include "noden.h"

class MCTree
{
public:
    MCTree(int width);
    ~MCTree();

    void add(NodeS *node);
    double sum() const;

    NodeS *find(double *r) const;

    void diagnostic() const;

private:
    int _width;
    NodeN *_root;
};

#endif // MCTREE_H

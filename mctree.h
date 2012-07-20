#ifndef MCTREE_H
#define MCTREE_H

#include "noden.h"
#include "inodes.h"

class MCTree
{
public:
    MCTree(int width);
    ~MCTree();

    void add(INodeS *node);
    double sum() const;

    INodeS *find(double *r) const;

    bool diagnostic() const;

private:
    int _width;
    NodeN *_root;
};

#endif // MCTREE_H

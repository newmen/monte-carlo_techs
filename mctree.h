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
    long double sum() const;

    INodeS *find(long double *r) const;

    void reCount();
    bool diagnostic() const;

private:
    int _width;
    NodeN *_root;
};

#endif // MCTREE_H

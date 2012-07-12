#ifndef INODES_H
#define INODES_H

#include "nodebase.h"

class INodeS : public NodeBase
{
public:
    virtual void initSum() = 0;
    virtual void doReactionOnSite(double r) = 0;

protected:
    INodeS() : NodeBase(0) {}
};

#endif // INODES_H

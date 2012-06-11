#ifndef NODEBASE_H
#define NODEBASE_H

class NodeBase
{
public:
    void setParent(NodeBase *parent) { _parent = parent; }
    int level() const { return _level; }
    float sum() const { return _sum; }

    void accSum(float sum);

protected:
    NodeBase(int level);

    NodeBase *parent() const { return _parent; }

    float _sum;

private:
    NodeBase *_parent;
    int _level;
};

#endif // NODEBASE_H

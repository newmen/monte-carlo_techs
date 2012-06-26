#ifndef NODEBASE_H
#define NODEBASE_H

class NodeBase
{
public:
    void setParent(NodeBase *parent) { _parent = parent; }
    int level() const { return _level; }
    double sum() const { return _sum; }

    void accSum(double sum);

    virtual void diagnoze() const = 0;

protected:
    NodeBase(int level);

    NodeBase *parent() const { return _parent; }

    double _sum;

private:
    NodeBase *_parent;
    int _level;
};

#endif // NODEBASE_H

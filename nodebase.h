#ifndef NODEBASE_H
#define NODEBASE_H

class NodeBase
{
public:
    virtual ~NodeBase() {}

    void setParent(NodeBase *parent) { _parent = parent; }
    int level() const { return _level; }
    double sum() const { return _sum; }

    void accSum(double sum);

    virtual bool diagnoze() const = 0;

protected:
    NodeBase(int level);

    NodeBase *parent() const { return _parent; }

    bool lessThanEps(double ds) const;

    double _sum;

private:
    NodeBase *_parent;
    int _level;
};

#endif // NODEBASE_H

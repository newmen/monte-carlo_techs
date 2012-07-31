#include "node_data.h"

#include <iostream>

NodeData::NodeData(int width, int level) : BaseNodeData(level), _width(width), _numberOfChilds(0) {
    _childs = new BaseNodeData *[_width];
    for (int i = 0; i < _width; ++i) _childs[i] = 0;
}

NodeData::~NodeData() {
    for (int i = 0; i < _numberOfChilds; ++i) delete _childs[i];
    delete [] _childs;
}

void NodeData::add(NodeSite *node) {
    if (level() > 1) {
        if (_numberOfChilds == 0 || last()->isFull()) store(new NodeData(_width, level() - 1));
        last()->add(node);
    } else {
        store(node);
    }
    _sum += node->sum();
}

void NodeData::add(NodeData *node) {
    store(node);
    _sum += node->sum();
}

bool NodeData::isFull() const {
    if (_numberOfChilds < _width) return false;
    if (level() == 1) return true;
    return last()->isFull();
}

NodeSite *NodeData::find(long double *r) const {
    for (int i = 0; i < _numberOfChilds; ++i) {
        long double childSum = _childs[i]->sum();
        if (*r < childSum) {
            if (level() == 1) {
                return static_cast<NodeSite *>(_childs[i]);
            } else {
                return static_cast<NodeData *>(_childs[i])->find(r);
            }
        } else {
            *r -= childSum;
        }
    }
    return 0; // happens when need reCount
}

void NodeData::reCount(const BaseSimulationContext *simulationContext) {
    _sum = 0;
    for (int i = 0; i < _numberOfChilds; ++i) {
        _childs[i]->reCount(simulationContext);
        _sum += _childs[i]->sum();
    }
}

bool NodeData::diagnoze() const {
    static int n = 0;
    ++n;

    long double childsSum  = 0;
    for (int i = 0; i < _numberOfChilds; ++i) {
        if (!_childs[i]->diagnoze()) return false;

        childsSum += _childs[i]->sum();
    }

    if (!lessThanEps(sum() - childsSum)) {
        std::cerr << n << ". Trouble on N" << level() << " level!\n"
                  << "diff: " << sum() - childsSum << std::endl;
        return false;
    }
    return true;
}

void NodeData::store(BaseNodeData *node) {
    node->setParent(this);
    _childs[_numberOfChilds++] = node;
}

NodeData *NodeData::last() const {
    return static_cast<NodeData *>(_childs[_numberOfChilds - 1]);
}

#include "mctree_data.h"

MCTreeData::MCTreeData(int width) : _width(width) {
    _root = new NodeData(_width, 1);
}

MCTreeData::~MCTreeData() {
    delete _root;
}

void MCTreeData::add(NodeSite *node) {
    node->initSum();
    if (_root->isFull()) {
        NodeData *newRoot = new NodeData(_width, _root->level() + 1);
        newRoot->add(_root);
        _root = newRoot;
    }
    _root->add(node);
}

long double MCTreeData::sum() const {
    return _root->sum();
}

NodeSite *MCTreeData::find(long double *r) const {
    return _root->find(r);
}

void MCTreeData::reCount(const BaseSimulationContext *simulationContext) {
    _root->reCount(simulationContext);
}

bool MCTreeData::diagnostic() const {
    return _root->diagnoze();
}


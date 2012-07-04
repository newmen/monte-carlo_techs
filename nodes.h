#ifndef NODES_H
#define NODES_H

#include "nodebase.h"
#include "persiteordimer_data.h"

#include <iostream>

class INodeS : public NodeBase
{
public:
    INodeS() : NodeBase(0) {}
};

template <class PerData>
class NodeS :
        public PerData,
        public INodeS
{
public:
    template <typename SharedData>
    NodeS(const SharedData &sharedData);

    void initSum();
    void updateRates();

    void diagnoze() const;

private:
    void updateSum();
};

template <class PerData>
template <typename SharedData>
NodeS<PerData>::NodeS(const SharedData &sharedData) : PerData(sharedData) {}

template <class PerData>
void NodeS<PerData>::initSum() {
    _sum = this->commonRate();
}

template <class PerData>
void NodeS<PerData>::updateRates() {
    PerData::updateRates();
    updateSum();
}

template <class PerData>
void NodeS<PerData>::updateSum() {
    if (parent()) parent()->accSum(this->commonRate() - _sum);
    _sum = this->commonRate();
}

template <class PerData>
void NodeS<PerData>::diagnoze() const {
    if (sum() != this->commonRate()) {
        std::cerr << "Trouble on S" << level() << " level!\n"
                  << "diff: " << sum() << " % " << this->commonRate() << std::endl;
    }
}

#endif // NODES_H

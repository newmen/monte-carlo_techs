#ifndef NODES_H
#define NODES_H

#include "inodes.h"
#include "perdimer.h"

#include <iostream>

// NodeS is a Role
template <class SmartSite>
class NodeS :
        public INodeS,
        public SmartSite
{
public:
    template <class SData>
    NodeS(SData *const site);

    void initSum();
    void doReactionOnSite(double r);

    void updateRates();
    void updateRates(const PerDimer *exceptPerDimer);
    void updateLocalCommonRate();

    void diagnoze() const;

private:
    void updateSum();
};

template <class SmartSite>
template <class SData>
NodeS<SmartSite>::NodeS(SData *const site) : SmartSite(site) {}

template <class SmartSite>
void NodeS<SmartSite>::initSum() {
    _sum = this->commonRate();
}

template <class SmartSite>
void NodeS<SmartSite>::doReactionOnSite(double r) {
    this->doReaction(r);
}

template <class SmartSite>
void NodeS<SmartSite>::updateRates() {
    SmartSite::updateRates();
    updateSum();
}

// this method only for PerSite instance
template <class SmartSite>
void NodeS<SmartSite>::updateRates(const PerDimer *exceptPerDimer) {
    SmartSite::updateRates(exceptPerDimer);
    updateSum();
}

// this method only for PerSite instance
template <class SmartSite>
void NodeS<SmartSite>::updateLocalCommonRate() {
    SmartSite::updateLocalCommonRate();
    updateSum();
}

template <class SmartSite>
void NodeS<SmartSite>::updateSum() {
    if (parent()) parent()->accSum(this->commonRate() - _sum);
    _sum = this->commonRate();
}

template <class SmartSite>
void NodeS<SmartSite>::diagnoze() const {
    if (sum() != this->commonRate()) {
        std::cerr << "Trouble on S" << level() << " level!\n"
                  << "diff: " << sum() << " % " << this->commonRate() << std::endl;
    }
}

#endif // NODES_H

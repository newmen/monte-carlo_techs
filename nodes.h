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
    void doReactionOnSite(const SimulationBaseContext *simulationContext, double r);

    void updateRates(const SimulationBaseContext *simulationContext);
    void updateRates(const SimulationBaseContext *simulationContext, const PerDimer *exceptPerDimer);
    void updateLocalCommonRate(const SimulationBaseContext *simulationContext, int otherSideIndex);

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
void NodeS<SmartSite>::doReactionOnSite(const SimulationBaseContext *simulationContext, double r) {
    this->doReaction(simulationContext, r);
}

template <class SmartSite>
void NodeS<SmartSite>::updateRates(const SimulationBaseContext *simulationContext) {
    SmartSite::updateRates(simulationContext);
    updateSum();
}

// this method only for PerSite instance
template <class SmartSite>
void NodeS<SmartSite>::updateRates(const SimulationBaseContext *simulationContext, const PerDimer *exceptPerDimer) {
    SmartSite::updateRates(simulationContext, exceptPerDimer);
    updateSum();
}

// this method only for PerSite instance
template <class SmartSite>
void NodeS<SmartSite>::updateLocalCommonRate(const SimulationBaseContext *simulationContext, int otherSideIndex) {
    SmartSite::updateLocalCommonRate(simulationContext, otherSideIndex);
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

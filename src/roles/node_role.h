#ifndef NODE_ROLE_H
#define NODE_ROLE_H

#include "../datas/nodesite_data.h"
#include "../datas/perdimer_data.h"

#include <iostream>

// NodeS is a Role
template <class PSData>
class NodeRole :
        public NodeSite,
        public PSData
{
public:
    template <class SData>
    NodeRole(SData *const site);

    void initSum();
    void doReaction(const BaseSimulationContext *simulationContext, long double r);

    void updateRates(const BaseSimulationContext *simulationContext);
    void updateRates(const BaseSimulationContext *simulationContext, const PerDimerData *exceptPerDimer);
    void updateLocalCommonRate(const BaseSimulationContext *simulationContext, int otherSideIndex);

    void reCount(const BaseSimulationContext *simulationContext);
    bool diagnoze() const;

private:
    void updateSum();
};

template <class PSData>
template <class SData>
NodeRole<PSData>::NodeRole(SData *const site) : PSData(site) {}

template <class PSData>
void NodeRole<PSData>::initSum() {
    _sum = this->commonRate();
}

template <class PSData>
void NodeRole<PSData>::doReaction(const BaseSimulationContext *simulationContext, long double r) {
    PSData::doReaction(simulationContext, r);
}

template <class PSData>
void NodeRole<PSData>::updateRates(const BaseSimulationContext *simulationContext) {
    PSData::updateRates(simulationContext);
    updateSum();
}

// this method only for PerSite instance
template <class PSData>
void NodeRole<PSData>::updateRates(const BaseSimulationContext *simulationContext, const PerDimerData *exceptPerDimer) {
    PSData::updateRates(simulationContext, exceptPerDimer);
    updateSum();
}

// this method only for PerSite instance
template <class PSData>
void NodeRole<PSData>::updateLocalCommonRate(const BaseSimulationContext *simulationContext, int otherSideIndex) {
    PSData::updateLocalCommonRate(simulationContext, otherSideIndex);
    updateSum();
}

template <class PSData>
void NodeRole<PSData>::reCount(const BaseSimulationContext *simulationContext) {
    PSData::updateRates(simulationContext);
    initSum();
}

template <class PSData>
void NodeRole<PSData>::updateSum() {
    if (this->commonRate() - _sum == 0.0) return;
    if (parent()) parent()->accSum(this->commonRate() - _sum);
    _sum = this->commonRate();
}

template <class PSData>
bool NodeRole<PSData>::diagnoze() const {
    if (!lessThanEps(sum() - this->commonRate())) {
        std::cerr << "Trouble on S" << level() << " level!\n"
                  << "diff: " << sum() - this->commonRate() << std::endl;
        return false;
    }
    return true;
}

#endif // NODE_ROLE_H

#include "nodes.h"

#include <iostream>

NodeS::NodeS(CellData *const cell) : NodeBase(0), PerCell(cell) {}

void NodeS::initSum() {
    _sum = commonRate();
}

void NodeS::updateRates() {
    PerCell::updateRates();
    updateSum();
}

void NodeS::updateRates(const PerDimer *exceptPerDimer) {
    PerCell::updateRates(exceptPerDimer);
    updateSum();
}

void NodeS::updateLocalCommonRate() {
    PerCell::updateLocalCommonRate();
    updateSum();
}

void NodeS::updateSum() {
    if (parent()) parent()->accSum(commonRate() - _sum);
    _sum = commonRate();
}

void NodeS::diagnoze() const {
    if (sum() != commonRate()) {
        std::cerr << "Trouble on S" << level() << " level!\n"
                  << "diff: " << sum() << " % " << commonRate() << std::endl;
    }
}

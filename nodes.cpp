#include "nodes.h"

#include <iostream>

NodeS::NodeS(int *cell, int **neighbours, int reactionsNum) :
    NodeBase(0), _site(cell, neighbours), _numberOfRates(reactionsNum)
{
    _rates = new double[_numberOfRates];
    for (int i = 0; i < _numberOfRates; ++i) _rates[i] = 0;
}

NodeS::~NodeS() {
    delete [] _rates;
}

SiteData &NodeS::site() {
    return _site;
}

void NodeS::rate(int index, double value) {
    _rates[index] = value;
}

void NodeS::updateSum() {
    double sum = 0;
    for (int i = 0; i < _numberOfRates; ++i) sum += _rates[i];
    if (parent()) parent()->accSum(sum - _sum);
    _sum = sum;
}

int NodeS::reactionIndex(double r) {
    for (int i = 0; i < _numberOfRates - 1; ++i) {
        if (r < _rates[i]) return i;
        else r -= _rates[i];
    }
    return _numberOfRates - 1;
}

void NodeS::diagnoze() const {
    double ratesSum = 0;
    for (int i = 0; i < _numberOfRates - 1; ++i) {
        ratesSum += _rates[i];
    }

    if (sum() != ratesSum) {
        std::cerr << "Trouble on S" << level() << " level!\n"
                  << "diff: " << sum() << " % " << ratesSum << std::endl;
    }
}


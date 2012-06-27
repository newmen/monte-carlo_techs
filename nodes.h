#ifndef NODES_H
#define NODES_H

#include "nodebase.h"
#include "site_data.h"

#include <iostream>

// чтобы можно было ссылаться не как на шаблон
class INodeS : public NodeBase {
protected:
    INodeS() : NodeBase(0) {}
};

template <int numberOfRates>
class NodeS : public INodeS
{
public:
    SiteData _site;
    double _rates[numberOfRates];

    NodeS(int *cell, int **neighbours);

    void updateSum();
    int reactionIndex(double r);

    void diagnoze() const;
};

template <int numberOfRates>
NodeS<numberOfRates>::NodeS(int *cell, int **neighbours) : _site(cell, neighbours) {
    for (int i = 0; i < numberOfRates; ++i) _rates[i] = 0;
}

template <int numberOfRates>
void NodeS<numberOfRates>::updateSum() {
    double sum = 0;
    for (int i = 0; i < numberOfRates; ++i) sum += _rates[i];
    if (parent()) parent()->accSum(sum - _sum);
    _sum = sum;
}

template <int numberOfRates>
int NodeS<numberOfRates>::reactionIndex(double r) {
    for (int i = 0; i < numberOfRates - 1; ++i) {
        if (r < _rates[i]) return i;
        else r -= _rates[i];
    }
    return numberOfRates - 1;
}

template <int numberOfRates>
void NodeS<numberOfRates>::diagnoze() const {
    double ratesSum = 0;
    for (int i = 0; i < numberOfRates - 1; ++i) {
        ratesSum += _rates[i];
    }

    if (sum() != ratesSum) {
        std::cout << "Trouble on S" << level() << " level!\n"
                  << "diff: " << sum() << " % " << ratesSum << std::endl;
    }
}

#endif // NODES_H

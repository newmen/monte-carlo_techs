#ifndef NODES_H
#define NODES_H

#include "nodebase.h"
#include "site_data.h"

class NodeS : public NodeBase
{
public:
    NodeS(int *cell, int **neighbours, int reactionsNum);
    ~NodeS();

    SiteData &site();
    void rate(int index, double value);

    void updateSum();
    int reactionIndex(double r);

    void diagnoze() const;

private:
    SiteData _site;
    double *_rates;
    int _numberOfRates;
};

#endif // NODES_H

#ifndef NODES_H
#define NODES_H

#include "nodebase.h"
#include "percell.h"

class NodeS :
        public NodeBase,
        public PerCell
{
public:
    NodeS(CellData *const cell);

    void initSum();
    void updateRates();
    void updateRates(const PerDimer *exceptPerDimer);
    void updateLocalCommonRate();

    void diagnoze() const;

private:
    void updateSum();
};

#endif // NODES_H

#ifndef CELLREACTION_DATA_H
#define CELLREACTION_DATA_H

#include "reaction_data.h"
#include "cell_data.h"

class CellReactionData : public ReactionData<CellData>
{
public:
    CellReactionData(double rateValue, int prevState, int nextState);

    double rate(const CellData *site) const;
    void doIt(CellData *const site) const;
};

#endif // CELLREACTION_DATA_H

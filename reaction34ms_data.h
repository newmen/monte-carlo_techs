#ifndef REACTION51MRS_DATA_H
#define REACTION51MRS_DATA_H

#include "reaction_data.h"

class Reaction34MSData : public ReactionData
{
public:
    Reaction34MSData() : ReactionData(5.9e1, 3, 3), _stableState(4) {}

protected:
    int stableState() const { return _stableState; }

private:
    int _stableState;
};

#endif // REACTION51MRS_DATA_H

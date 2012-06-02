#ifndef REACTION21_DATA_H
#define REACTION21_DATA_H

#include "reaction_data.h"

class Reaction21Data : public ReactionData
{
public:
    Reaction21Data() : ReactionData(5e-1, 2, 1) {}
};

#endif // REACTION21_DATA_H

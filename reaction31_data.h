#ifndef REACTION31_ROLE_H
#define REACTION31_ROLE_H

#include "reaction_data.h"

class Reaction31Data : public ReactionData
{
public:
    Reaction31Data() : ReactionData(1e2, 3, 1) {}
};

#endif // REACTION31_ROLE_H

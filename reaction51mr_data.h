#ifndef REACTION51MR_DATA_H
#define REACTION51MR_DATA_H

#include "reaction_data.h"

class Reaction51MRData : public ReactionData
{
public:
    Reaction51MRData() : ReactionData(4e2, 5, 1), _migrationsNum(0) {}

protected:
    void incMigrationsNum() { ++_migrationsNum; }
    int migrationsNum() const { return _migrationsNum; }

private:
    int _migrationsNum;
};

#endif // REACTION51MR_DATA_H

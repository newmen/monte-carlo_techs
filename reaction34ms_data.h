#ifndef REACTION34MS_DATA_H
#define REACTION34MS_DATA_H

#include "reaction34_data.h"

class Reaction34MSData : public Reaction34Data
{
public:
    Reaction34MSData() : _stableState(Reaction34Data::nextState()) {}

protected:
    int nextState() const { return 3; }
    int stableState() const { return _stableState; }

private:
    int _stableState;
};

#endif // REACTION34MS_DATA_H

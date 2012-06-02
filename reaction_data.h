#ifndef REACTION_DATA_H
#define REACTION_DATA_H

class ReactionData
{
protected:
    ReactionData(float rateValue, int prevState, int nextState) :
        _rateValue(rateValue), _prevState(prevState), _nextState(nextState) {}

    float rateValue() const { return _rateValue; }
    int prevState() const { return _prevState; }
    int nextState() const { return _nextState; }

private:
    float _rateValue;
    int _prevState, _nextState;
};

#endif // REACTION_DATA_H

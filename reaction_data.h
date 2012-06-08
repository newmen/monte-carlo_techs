#ifndef REACTION_DATA_H
#define REACTION_DATA_H

class ReactionData
{
public:
    float k() const { return _k; }

protected:
    ReactionData(float rateValue, int prevState, int nextState) :
        _k(rateValue), _prevState(prevState), _nextState(nextState) {}

    int prevState() const { return _prevState; }
    int nextState() const { return _nextState; }

private:
    float _k;
    int _prevState, _nextState;
};

#endif // REACTION_DATA_H

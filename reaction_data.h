#ifndef REACTION_DATA_H
#define REACTION_DATA_H

template <class SData>
class ReactionData
{
public:
    virtual ~ReactionData() {}

    virtual double rate(const SData *site) const = 0;
    virtual void doIt(SData *const site) const = 0;

    float k() const { return _k; }
    int prevState() const { return _prevState; }
    int nextState() const { return _nextState; }

protected:
    ReactionData(float k, int prevState, int nextState) :
        _k(k), _prevState(prevState), _nextState(nextState) {}

    virtual double rateValue(const SData *) const { return _k; }

private:
    float _k;
    int _prevState, _nextState;
};

#endif // REACTION_DATA_H

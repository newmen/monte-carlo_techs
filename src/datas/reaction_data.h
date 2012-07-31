#ifndef REACTION_DATA_H
#define REACTION_DATA_H

template <class SData>
class ReactionData
{
public:
    virtual ~ReactionData() {}

    virtual long double rate(const SData *site) const = 0;
    virtual void doIt(SData *const site) const = 0;

    long double k() const { return _k; }
    int prevState() const { return _prevState; }
    int nextState() const { return _nextState; }

protected:
    ReactionData(long double k, int prevState, int nextState) :
        _k(k), _prevState(prevState), _nextState(nextState) {}

    virtual long double rateValue(const SData *) const { return _k; }

private:
    long double _k;
    int _prevState, _nextState;
};

#endif // REACTION_DATA_H

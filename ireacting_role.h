#ifndef IREACTING_ROLE_H
#define IREACTING_ROLE_H

template <class SData>
class IReactingRole
{
public:
    virtual ~IReactingRole() {}

    virtual double rate(const SData &site) const = 0;
    virtual void doIt(SData *const site) const = 0;

protected:
    IReactingRole() {}
};

#endif // IREACTING_ROLE_H

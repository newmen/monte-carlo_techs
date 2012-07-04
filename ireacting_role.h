#ifndef IREACTING_ROLE_H
#define IREACTING_ROLE_H

template <class SDData>
class IReactingRole
{
public:
    virtual ~IReactingRole() {}

    virtual double rate(const SDData &siteOrDimer) const = 0;
    virtual void doIt(SDData *siteOrDimer) const = 0;

protected:
    IReactingRole() {}
};

#endif // IREACTING_ROLE_H

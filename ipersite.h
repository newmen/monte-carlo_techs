#ifndef IPERSITE_H
#define IPERSITE_H

class IPerSite
{
public:
    virtual ~IPerSite() {}

    virtual double commonRate() const = 0;
    virtual void doReaction(double r) = 0;

protected:
    IPerSite() {}
};

#endif // IPERSITE_H

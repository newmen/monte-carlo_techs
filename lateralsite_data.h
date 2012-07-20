#ifndef LATERALSITE_DATA_H
#define LATERALSITE_DATA_H

class LateralSiteData
{
public:
    ~LateralSiteData();

    void resetNumsOfSpec(int numOfSpecs);
    void incNumOfSpec(int index) { ++_spec[index]; }
    int numOfSpec(int index) const { return _spec[index]; }

protected:
    LateralSiteData(int numOfSpecs);

private:
    int *_spec;
};

#endif // LATERALSITE_DATA_H

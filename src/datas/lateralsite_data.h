#ifndef LATERALSITE_DATA_H
#define LATERALSITE_DATA_H

class LateralSiteData
{
public:
    ~LateralSiteData();

    void resetNumsOfSpecs(int numOfSpecs);
    void incNumOfSpec(int index) { ++_numsOfSpecs[index]; }
    int numOfSpec(int index) const { return _numsOfSpecs[index]; }

protected:
    LateralSiteData(int numOfSpecs);

private:
    int *_numsOfSpecs;
};

#endif // LATERALSITE_DATA_H

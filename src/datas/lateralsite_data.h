#ifndef LATERALSITE_DATA_H
#define LATERALSITE_DATA_H

class LateralSiteData
{
public:
    ~LateralSiteData();

    void resetNumsOfSpecs(short numOfSpecs);
    void incNumOfSpec(short index) { ++_numsOfSpecs[index]; }
    int numOfSpec(short index) const { return _numsOfSpecs[index]; }

protected:
    LateralSiteData(short numOfSpecs);

private:
    short *_numsOfSpecs;
};

#endif // LATERALSITE_DATA_H

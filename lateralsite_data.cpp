#include "lateralsite_data.h"

LateralSiteData::LateralSiteData(int numOfSpecs) {
    _numsOfSpecs = new int[numOfSpecs];
}

LateralSiteData::~LateralSiteData() {
    delete [] _numsOfSpecs;
}

void LateralSiteData::resetNumsOfSpecs(int numOfSpecs) {
    for (int i = 0; i < numOfSpecs; ++i) _numsOfSpecs[i] = 0;
}

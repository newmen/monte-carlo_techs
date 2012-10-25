#include "lateralsite_data.h"

LateralSiteData::LateralSiteData(short numOfSpecs) {
    _numsOfSpecs = new short[numOfSpecs];
}

LateralSiteData::~LateralSiteData() {
    delete [] _numsOfSpecs;
}

void LateralSiteData::resetNumsOfSpecs(short numOfSpecs) {
    for (short i = 0; i < numOfSpecs; ++i) _numsOfSpecs[i] = 0;
}

#include "lateralsite_data.h"

LateralSiteData::LateralSiteData(int numOfSpecs) {
    _spec = new int[numOfSpecs];
}

LateralSiteData::~LateralSiteData() {
    delete [] _spec;
}

void LateralSiteData::resetNumsOfSpec(int numOfSpecs) {
    for (int i = 0; i < numOfSpecs; ++i) _spec[i] = 0;
}

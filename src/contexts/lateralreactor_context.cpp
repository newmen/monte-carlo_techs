#include "lateralreactor_context.h"
#include "../datas/lateralcell_data.h"
#include "../datas/lateraldimer_data.h"
#include "../roles/neighbouring_role.h"

LateralReactorContext::LateralReactorContext(double T) : RTReactorContext(T) {}

CellData *LateralReactorContext::createCell(CellType *cell, CoordType x, CoordType y) const {
    return new LateralCellData(cell, x, y, numOfSpecs());
}

DimerData *LateralReactorContext::createDimer(CellData *first, CellData *second) const {
    return new LateralDimerData(first, second, numOfSpecs());
}

void LateralReactorContext::reinitCell(CellData *cell, const AreaData *area) const {
    reinitSite<CellData, LateralCellData>(cell, area);
}

void LateralReactorContext::reinitDimer(DimerData *dimer, const AreaData *area) const {
    reinitSite<DimerData, LateralDimerData>(dimer, area);
}

template <class SData, class LData>
void LateralReactorContext::reinitSite(SData *site, const AreaData *area) const {
    LData *lateralSite = static_cast<LData *>(site);
    lateralSite->resetNumsOfSpecs(numOfSpecs());
    static_cast<NeighbouringRole<SData> *>(site)->eachNeighbour(area, isTorusArea(), [this, &area, &lateralSite](int neighbourIndex) {
        int value = area->value(neighbourIndex);
        if (value > 1) lateralSite->incNumOfSpec(value - 2);
    });
}

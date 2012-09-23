#include <ostream>
#include "nocoreactor_context.h"
#include "../datas/lateralcell_data.h"
#include "../datas/lateraldimer_data.h"
#include "../datas/cellreaction_data.h"
#include "../datas/celllateralreaction_data.h"
#include "../datas/dimerlateralreactionexplosion_data.h"
#include "../datas/dimerreactionexchange_data.h"
#include "../roles/neighbouring_role.h"

NOCOReactorContext::NOCOReactorContext() : RTReactorContext(404) {
    double pNO = 3.7e-6;
    double pCO = 3e-6;
    addReaction(new CellReactionData(1, 2, 1.93e5 * pNO));
    addReaction(new DimerReactionExchangeData(2, 1, 250));
    addReaction(new CellReactionData(1, 3, 1.93e5 * pCO));
    addReaction(new DimerReactionExchangeData(3, 1, 250));

    long double eps3[] = {-2e3, -0.8e3};
    addReaction(new DimerLateralReactionExplosionData(2, 3, 1, 2e15 / 4, 24.5e3, eps3, this));
    long double eps4[] = {1.8e3, 2.2e3};
    addReaction(new CellLateralReactionData(2, 1, 2e15, 37e3, eps4, this));
    long double eps5[] = {2.2e3, 1e3};
    addReaction(new CellLateralReactionData(3, 1, 1e15, 37.5e3, eps5, this));
}

CellData *NOCOReactorContext::createCell(CellType *cell, CoordType x, CoordType y) const {
    return new LateralCellData(cell, x, y, numOfSpecs());
}

DimerData *NOCOReactorContext::createDimer(CellData *first, CellData *second) const {
    return new LateralDimerData(first, second, numOfSpecs());
}

void NOCOReactorContext::reinitCell(CellData *cell, const AreaData *area) const {
    reinitSite<CellData, LateralCellData>(cell, area);
}

void NOCOReactorContext::reinitDimer(DimerData *dimer, const AreaData *area) const {
    reinitSite<DimerData, LateralDimerData>(dimer, area);
}

void NOCOReactorContext::solveToOut(std::ostream &out) const {
}

template <class SData, class LData>
void NOCOReactorContext::reinitSite(SData *site, const AreaData *area) const {
    LData *lateralSite = static_cast<LData *>(site);
    lateralSite->resetNumsOfSpecs(numOfSpecs());
    static_cast<NeighbouringRole<SData> *>(site)->eachNeighbour(area, [this, &area, &lateralSite](int neighbourIndex) {
        int value = area->value(neighbourIndex);
        if (value > 1) lateralSite->incNumOfSpec(value - 2);
    });
}

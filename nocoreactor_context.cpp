#include <ostream>
#include "nocoreactor_context.h"
#include "lateralcell_data.h"
#include "lateraldimer_data.h"
#include "cellreaction_data.h"
#include "celllateralreaction_data.h"
#include "dimerlateralreactionexplosion_data.h"
#include "dimerreactionexchange_data.h"
#include "neighbouring_role.h"

NOCOReactorContext::NOCOReactorContext() : RTReactorContext(404) {
    double pNO = 3.7e-6;
    double pCO = 3e-6;
    addReaction(new CellReactionData(1.93e5 * pNO, 1, 2));
    addReaction(new DimerReactionExchangeData(1000, 2, 1));
    addReaction(new CellReactionData(1.93e5 * pCO, 1, 3));
    addReaction(new DimerReactionExchangeData(1000, 3, 1));

    long double eps3[] = {-2e3, -0.8e3};
    addReaction(new DimerLateralReactionExplosionData(2, 3, 1, this, 2e15 / 4, 24.5e3, eps3));
    long double eps4[] = {1.8e3, 2.2e3};
    addReaction(new CellLateralReactionData(2, 1, this, 2e15, 37e3, eps4));
    long double eps5[] = {2.2e3, 1e3};
    addReaction(new CellLateralReactionData(3, 1, this, 1e15, 37.5e3, eps5));
}

CellData *NOCOReactorContext::createCell(int *cell, int x, int y) const {
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

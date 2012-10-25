#include <cmath>
#include <ostream>
#include "nocoreactor_context.h"
#include "flatwavedistribution_context.h"
#include "spiralwavedistribution_context.h"
#include "../datas/lateralcell_data.h"
#include "../datas/lateraldimer_data.h"
#include "../datas/cellreaction_data.h"
#include "../datas/celllateralreaction_data.h"
#include "../datas/dimerlateralreactionexplosion_data.h"
#include "../datas/dimerreactionexchange_data.h"
#include "../roles/neighbouring_role.h"

NOCOReactorContext::NOCOReactorContext() : RTReactorContext(406) {
    double pNO = 3.7e-6;
    double pCO = 3e-6;
    addReaction(new CellReactionData(1, 2, 1.93e5 * pNO));
    addReaction(new DimerReactionExchangeData(2, 1, 15));
    addReaction(new CellReactionData(1, 3, 1.93e5 * pCO));
    addReaction(new DimerReactionExchangeData(3, 1, 15));

    long double eps3[] = {-2e3, -0.8e3};
    addReaction(new DimerLateralReactionExplosionData(2, 3, 1, 2e15 / 4, 24.5e3, eps3, this));
    long double eps4[] = {1.8e3, 2.2e3};
    addReaction(new CellLateralReactionData(2, 1, 2e15, 37e3, eps4, this));
    long double eps5[] = {2.2e3, 1e3};
    addReaction(new CellLateralReactionData(3, 1, 1e15, 37.5e3, eps5, this));
}

bool NOCOReactorContext::isTorusArea() const {
//    return true;
    return false;
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

BaseDistributionContext *NOCOReactorContext::createDistrubutor() const {
//     float concs[] = {
//         0.067, 0.223,
//         0.249, 0.504,
//         0.533, 0.292,
//         0.319, 0.104
//     };
    // return new FlatWaveDistributionContext(concs, 2);
//    return new SpiralWaveDistributionContext(concs, 2);

    float concs[] = { 0.1, 0.1 };
    return new SimpleDistributionContext(concs, 2);
}

// копипакость
void NOCOReactorContext::solveToOut(std::ostream &out) const {
    long double dt = timeStep();
    long double currentTime = 0;

    long double *concs = new long double[numOfSpecs()];
    for (int i = 0; i < numOfSpecs(); ++i) concs[i] = 0;
    long double *csNext = new long double[numOfSpecs()];

    const CellReactionData *adsorbNO = static_cast<const CellReactionData *>(cellReaction(0));
    const CellReactionData *adsorbCO = static_cast<const CellReactionData *>(cellReaction(1));
    const CellLateralReactionData *desorbNO = static_cast<const CellLateralReactionData *>(cellReaction(2));
    const CellLateralReactionData *desorbCO = static_cast<const CellLateralReactionData *>(cellReaction(3));
    const DimerLateralReactionExplosionData *makeCO2 = static_cast<const DimerLateralReactionExplosionData *>(dimerReaction(2));

    while (currentTime < maxTime()) {
        long double csSum = 0;
        for (int i = 0; i < numOfSpecs(); ++i) csSum += concs[i];

        long double emptyConc = 1 - csSum;

        long double I1 = pow(emptyConc + concs[0] * exp(desorbNO->eps(0) / RT()) + concs[1] * exp(desorbNO->eps(1) / RT()), 4);
        long double I2 = pow(emptyConc + concs[0] * exp(desorbCO->eps(0) / RT()) + concs[1] * exp(desorbCO->eps(1) / RT()), 4);
        long double I3 = pow(emptyConc + concs[0] * exp(makeCO2->eps(0) / RT()) + concs[1] * exp(makeCO2->eps(1) / RT()), 6);

        long double K3 = desorbNO->k() * exp(-desorbNO->Ea() / RT());
        long double K4 = desorbCO->k() * exp(-desorbCO->Ea() / RT());
        long double K5 = 4 * makeCO2->k() * exp(-makeCO2->Ea() / RT());

        long double makeCO2part = K5 * concs[0] * concs[1] * I3;
        csNext[0] = concs[0] + dt * (adsorbNO->k() * emptyConc - K3 * concs[0] * I1 - makeCO2part);
        csNext[1] = concs[1] + dt * (adsorbCO->k() * emptyConc - K4 * concs[1] * I2 - makeCO2part);

        currentTime += dt;
        out << currentTime;
        for (int i = 0; i < numOfSpecs(); ++i) {
            concs[i] = csNext[i];
            out << "\t" << concs[i];
        }
        out << std::endl;
    }

    delete [] csNext;
    delete [] concs;
}

template <class SData, class LData>
void NOCOReactorContext::reinitSite(SData *site, const AreaData *area) const {
    LData *lateralSite = static_cast<LData *>(site);
    lateralSite->resetNumsOfSpecs(numOfSpecs());
    static_cast<NeighbouringRole<SData> *>(site)->eachNeighbour(area, isTorusArea(), [this, &area, &lateralSite](int neighbourIndex) {
        int value = area->value(neighbourIndex);
        if (value > 1) lateralSite->incNumOfSpec(value - 2);
    });
}

#include <cmath>
#include <ostream>
#include "fullnocoreactor_context.h"
#include "flatwavedistribution_context.h"
#include "spiralwavedistribution_context.h"
#include "../datas/cellreaction_data.h"
#include "../datas/celllateralreaction_data.h"
#include "../datas/dimerreactionactivationexplosion_data.h"
#include "../datas/dimerlateralreactiondissociation_data.h"
#include "../datas/dimerreactionexchange_data.h"

FullNOCOReactorContext::FullNOCOReactorContext() : LateralReactorContext(410) {
    double pNO = 4e-7;
    double pCO = 3e-7;
    addReaction(new CellReactionData(1, 2, 2.21e5 * pNO));
    addReaction(new CellReactionData(1, 3, 2.21e5 * pCO));

    long double eps3[] = {1.5e3, 1.5e3, 1.5e3};
    addReaction(new CellLateralReactionData(2, 1, 1.7e15, 37e3, eps3, this));

    long double eps4[] = {1.5e3, 1e3, 1.5e3};
    addReaction(new CellLateralReactionData(3, 1, 1e15, 37.5e3, eps4, this));

    addReaction(new DimerReactionActivationExplosionData(3, 4, 1, 5e8, 12e3, this));

    long double eps6[] = {-1.5e3, 0, -1.5e3};
    addReaction(new DimerLateralReactionDissociationData(1, 2, 4, 1, 5e14, 28e3, eps6, this));

    double migrationRate = 150;
    addReaction(new DimerReactionExchangeData(2, 1, migrationRate));
    addReaction(new DimerReactionExchangeData(3, 1, migrationRate));
    addReaction(new DimerReactionExchangeData(4, 1, migrationRate));
}

bool FullNOCOReactorContext::isTorusArea() const {
    return true;
}

BaseDistributionContext *FullNOCOReactorContext::createDistrubutor() const {
//     float concs[] = {
//         0.195, 0.010, 0.010,
//         0.531, 0.013, 0.002,
//         0.574, 0.261, 0.000,
//         0.444, 0.332, 0.000
//     };
    // return new FlatWaveDistributionContext(concs, 3);
//    return new SpiralWaveDistributionContext(concs, 3);

    float concs[] = { 0.195, 0.010, 0.010 };
    return new SimpleDistributionContext(concs, 3);
}

void FullNOCOReactorContext::solveToOut(std::ostream &out) const {
    long double dt = timeStep() / 20;
    long double currentTime = 0;

    long double *concs = new long double[numOfSpecs()];
    concs[0] = 0.195;
    concs[1] = 0.010;
    concs[2] = 0.010;
    long double *csNext = new long double[numOfSpecs()];

    const CellReactionData *adsorbNO = static_cast<const CellReactionData *>(cellReaction(0));
    const CellReactionData *adsorbCO = static_cast<const CellReactionData *>(cellReaction(1));
    const CellLateralReactionData *desorbNO = static_cast<const CellLateralReactionData *>(cellReaction(2));
    const CellLateralReactionData *desorbCO = static_cast<const CellLateralReactionData *>(cellReaction(3));
    const DimerReactionActivationExplosionData *makeCO2 = static_cast<const DimerReactionActivationExplosionData *>(dimerReaction(0));
    const DimerLateralReactionDissociationData *dissocNO = static_cast<const DimerLateralReactionDissociationData *>(dimerReaction(1));

    while (currentTime < maxTime()) {
        long double csSum = 0;
        for (int i = 0; i < numOfSpecs(); ++i) csSum += concs[i];

        long double emptyConc = 1 - csSum;

        long double S3 = pow(emptyConc + concs[0] * exp(desorbNO->eps(0) / RT()) + concs[1] * exp(desorbNO->eps(1) / RT()) + concs[2] * exp(desorbNO->eps(2) / RT()), 4);
        long double S4 = pow(emptyConc + concs[0] * exp(desorbCO->eps(0) / RT()) + concs[1] * exp(desorbCO->eps(1) / RT()) + concs[2] * exp(desorbCO->eps(2) / RT()), 4);
        long double S6 = pow(emptyConc + concs[0] * exp(dissocNO->eps(0) / RT()) + concs[1] * exp(dissocNO->eps(1) / RT()) + concs[2] * exp(dissocNO->eps(2) / RT()), 6);

        long double K3 = desorbNO->k() * exp(-desorbNO->Ea() / RT());
        long double K4 = desorbCO->k() * exp(-desorbCO->Ea() / RT());
        long double K5 = 4 * makeCO2->k() * exp(-makeCO2->Ea() / RT());
        long double K6 = 4 * dissocNO->k() * exp(-dissocNO->Ea() / RT());

        long double makeCO2part = K5 * concs[1] * concs[2];
        long double dissocNOpart = K6 * concs[0] * emptyConc * S6;
        csNext[0] = concs[0] + dt * (adsorbNO->k() * emptyConc - K3 * concs[0] * S3 - dissocNOpart);
        csNext[1] = concs[1] + dt * (adsorbCO->k() * emptyConc - K4 * concs[1] * S4 - makeCO2part);
        csNext[2] = concs[2] + dt * (dissocNOpart - makeCO2part);

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

#include <fstream>
#include <iostream>
#include "abcdreactor_data.h"
#include "cellreaction_data.h"

ABCDReactorData::ABCDReactorData() {
    addReaction(new CellReactionData(144, 1, 2));
    addReaction(new CellReactionData(34, 2, 1));
    addReaction(new CellReactionData(55, 2, 3));
}

CellData *ABCDReactorData::createCell(int *cell, int x, int y) const {
    return new CellData(cell, x, y);
}

void ABCDReactorData::solve(const std::string &fileName, double maxTime) const {
    std::ofstream out(fileName);
    if (!out) {
        std::cerr << "File " << fileName << " open error!" << std::endl;
        return;
    }

    double ratesSum = 0;
    int numOfSpecs = 0;
    std::function<void (const ReactionData<CellData> *const)> lambda =
            [&numOfSpecs, &ratesSum](const ReactionData<CellData> *const reaction)
    {
        if (reaction->prevState() > 1) ++numOfSpecs;
        ratesSum += reaction->k();
    };
    eachReaction(lambda);

    double currentTime = 0;
    double dt = ratesSum / 5e5;
    double *concs = new double[numOfSpecs];
    for (int i = 0; i < numOfSpecs; ++i) concs[i] = 0;
    double *csNext = new double[numOfSpecs];

    while (currentTime < maxTime) {
        double csSum = 0;
        for (int i = 0; i < numOfSpecs; ++i) csSum += concs[i];

        for (int i = 0; i < numOfSpecs; ++i) {
            double dc = 0;
            std::function<void (const ReactionData<CellData> *const)> lambda =
                    [numOfSpecs, concs, csSum, i, &dc](const ReactionData<CellData> *const reaction)
            {
                int nextIndex = reaction->nextState() - 2;
                int prevIndex = reaction->prevState() - 2;
                if (nextIndex == i) {
                    if (reaction->prevState() == 1) {
                        dc += reaction->k() * (1 - csSum);
                    } else {
                        dc += reaction->k() * concs[prevIndex];
                    }
                } else if (prevIndex == i) {
                    dc -= reaction->k() * concs[i];
                }
            };
            eachReaction(lambda);
            csNext[i] = concs[i] + dt * dc;
        }

        for (int i = 0; i < numOfSpecs; ++i) concs[i] = csNext[i];
        currentTime += dt;

        out << currentTime;
        for (int i = 0; i < numOfSpecs; ++i) out << "\t" << concs[i];
        out << std::endl;
    }

    delete [] csNext;
    delete [] concs;
}

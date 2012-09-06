#include <ostream>
#include "abcdreactor_context.h"
#include "../datas/cellreaction_data.h"
#include "../datas/dimerreactionexchange_data.h"

ABCDReactorContext::ABCDReactorContext() {
    addReaction(new CellReactionData(1, 2, 144));
    addReaction(new CellReactionData(2, 1, 34));
    addReaction(new CellReactionData(2, 3, 55));
    addReaction(new DimerReactionExchangeData(3, 1, 1e2));
}

void ABCDReactorContext::solveToOut(std::ostream &out) const {
    long double ratesSum = 0;
    std::function<void (const ReactionData<CellData> *const)> lambda =
            [&ratesSum](const ReactionData<CellData> *const reaction)
    {
        ratesSum += reaction->k();
    };
    eachReaction(lambda);

    long double currentTime = 0;
    long double dt = ratesSum / 5e5;
    long double *concs = new long double[numOfSpecs()];
    for (int i = 0; i < numOfSpecs(); ++i) concs[i] = 0;
    long double *csNext = new long double[numOfSpecs()];

    while (currentTime < maxTime()) {
        long double csSum = 0;
        for (int i = 0; i < numOfSpecs(); ++i) csSum += concs[i];

        for (int i = 0; i < numOfSpecs(); ++i) {
            long double dc = 0;
            std::function<void (const ReactionData<CellData> *const)> lambda =
                    [concs, csSum, i, &dc](const ReactionData<CellData> *const reaction)
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

        for (int i = 0; i < numOfSpecs(); ++i) concs[i] = csNext[i];
        currentTime += dt;

        out << currentTime;
        for (int i = 0; i < numOfSpecs(); ++i) out << "\t" << concs[i];
        out << std::endl;
    }

    delete [] csNext;
    delete [] concs;
}

#include <cmath>
#include <cstdlib>
#include "dynamicsimulation_context.h"

//#define DEBUG_OUT

#ifdef DEBUG_OUT
#include <iostream>
#endif

DynamicSimulationContext::DynamicSimulationContext(AreaData *area) : SimulationBaseContext(area) {
}

DynamicSimulationContext::~DynamicSimulationContext() {
}

float DynamicSimulationContext::doReaction() {

#ifdef DEBUG_OUT
    std::cout << "-------------------------" << std::endl;
#endif

    collectSites();

    int totalReactions = 0;
    for (int n : _numberOfReactions) totalReactions += n;
    if (totalReactions == 0) return 0;

    float totalRate = 0;
    int reactionIndex = proportionalReactionRandomIndex(&totalRate);
    reaction(reactionIndex)->doIt(randomSite(reactionIndex));

    return negativLogU() / totalRate;
}

void DynamicSimulationContext::collectSites() {
    for (int i = 0; i < REACTIONS_NUM; ++i) {
        _numberOfReactions[i] = 0;
        _sites[i].clear();
    }

#ifdef DEBUG_OUT
    auto printLambda = [this](const char *name) {
        std::cout << name << ":" << std::endl;
        for (int i = 0; i < REACTIONS_NUM; ++i) {
            std::cout << "   " << _sites[i].size() << "(" << _numberOfReactions[i] << ")";
        }
        std::cout << std::endl;
    };
    printLambda("before");
#endif

    throughArea([this](int *cell, int **neighbours) {
        SiteData site(cell, neighbours);
        for (int i = 0; i < REACTIONS_NUM; ++i) {
            int reactionsNum = reaction(i)->couldBe(site);
            if (reactionsNum > 0) {
                _numberOfReactions[i] += reactionsNum;
                _sites[i].push_back(site);
            }
        }
    });

#ifdef DEBUG_OUT
    printLambda("after");
#endif
}

int DynamicSimulationContext::proportionalReactionRandomIndex(float *totalRate) const {
    float rates[REACTIONS_NUM];
    for (int i = 0; i < REACTIONS_NUM; ++i) {
        rates[i] = _numberOfReactions[i] * reaction(i)->rate();
    }

    for (float n : rates) *totalRate += n;

#ifdef DEBUG_OUT
    auto printArrLambda = [](const char *name, float arr[REACTIONS_NUM]) {
        std::cout << name << ":" << std::endl;
        for (int i = 0; i < REACTIONS_NUM; ++i) {
            std::cout << "   " << arr[i];
        }
        std::cout << std::endl;
    };
    printArrLambda("rates", rates);

    auto printValueLambda = [](const char *name, float value) {
        std::cout << name << " = " << value << std::endl;
    };
    printValueLambda("totalRate", *totalRate);
#endif

    float normalizedRates[REACTIONS_NUM];
    for (int i = 0; i < REACTIONS_NUM; ++i) {
        normalizedRates[i] = rates[i] / *totalRate;
    }

    for (int i = 1; i < REACTIONS_NUM; ++i) {
        normalizedRates[i] += normalizedRates[i - 1];
    }

#ifdef DEBUG_OUT
    printArrLambda("normalizedRates", normalizedRates);
#endif

    int randomIndex = REACTIONS_NUM - 1;
    float r = randomN01(); // TODO: тут нужно учитывать то, что иногда нормированные скорости дают чуть больше единицы
#ifdef DEBUG_OUT
    printValueLambda("r", r);
#endif
    for (int i = 0; i < REACTIONS_NUM - 1; ++i) {
        if (r < normalizedRates[i]) {
            randomIndex = i;
            break;
        }
    }
#ifdef DEBUG_OUT
    printValueLambda("randomIndex", randomIndex);
#endif
    return randomIndex;
}

SiteData *DynamicSimulationContext::randomSite(int reactionIndex) {
    int randomIndex = rand() % _sites[reactionIndex].size();
    auto it = _sites[reactionIndex].begin();
    advance(it, randomIndex);
    return &(*it);
}
